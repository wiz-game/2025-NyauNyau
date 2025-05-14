#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowObject.h"
#include "RaycastLine.h"

namespace basecross
{
    std::vector<std::shared_ptr<RaycastLine>> activeRays; // レイ管理リスト

    void ShadowObject::OnCreate()
    {
        m_drawComp = AddComponent<PNTStaticDraw>();
        m_drawComp->SetOriginalMeshUse(true);
    }

    void ShadowObject::OnUpdate()
    {
        auto& app = App::GetApp();
        auto scene = app->GetScene<Scene>();

        wstring log = scene->GetDebugString();
        wstringstream wss;
        wss << log;

        // 光源位置を確認
        auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        m_lightPos = light->GetComponent<Transform>()->GetPosition();
        wss << L"Light Position: " << m_lightPos.x << L", " << m_lightPos.y << L", " << m_lightPos.z << L"\n";

        auto boxVertices = GetBoxVertices();
        auto shadowIntersections = ComputeShadowIntersections(m_lightPos, boxVertices);

        // 交点デバッグ表示
        wss << L"Shadow Intersections Count: " << shadowIntersections.size() << L"\n";
        for (const auto& intersection : shadowIntersections)
        {
            wss << L"Intersection: " << intersection.x << L", " << intersection.y << L", " << intersection.z << L"\n";
        }

        //修正: 凸包計算後の交点確認
        std::vector<Vec2> projectedVertices;
        for (const auto& vertex : shadowIntersections)
        {
            projectedVertices.push_back(Vec2(vertex.z, vertex.y)); //Zを横、Yを上下として処理
        }

        //`ComputeConvexHull` のデバッグログを統合
        wss << L"Initial Vertex Count: " << projectedVertices.size() << L"\n";

        BubbleSort(projectedVertices);

        wss << L"After Sorting:\n";
        for (const auto& v : projectedVertices)
        {
            wss << L"Vertex: " << v.x << L", " << v.y << L"\n";
        }

        m_shadowVertices = ComputeConvexHull(projectedVertices);

        wss << L"Final Convex Hull Count: " << m_shadowVertices.size() << L"\n";

        //シーンにデバッグログを適用
        scene->SetDebugString(wss.str());

        // 影ポリゴンを生成
        CreatePolygonMesh(m_shadowVertices);
    }

    std::vector<Vec3> ShadowObject::ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& boxVertices)
    {
        std::vector<Vec3> intersections;

        auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        if (!wall)
            return intersections;

        Vec3 wallNormal = wall->GetWallNormal();
        Vec3 wallPoint = wall->GetWallPosition();
        Vec4 wallPlane = GeneratePlane(wallPoint, wallNormal);

        for (const auto& vertex : boxVertices)
        {
            Vec3 lightDir = Vec3(vertex - lightPos).normalize();

            //平面との交点を計算
            float denominator = wallPlane.x * lightDir.x + wallPlane.y * lightDir.y + wallPlane.z * lightDir.z;
            if (fabs(denominator) < 1e-6f)
                continue;

            float t = -(wallPlane.x * lightPos.x + wallPlane.y * lightPos.y + wallPlane.z * lightPos.z + wallPlane.w) / denominator;
            if (t < 0)
                continue;

            Vec3 intersection = lightPos + lightDir * t;
            intersections.push_back(intersection);
        }

        return intersections;
    }

    Vec4 ShadowObject::GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal)
    {
        return Vec4(wallNormal.x, wallNormal.y, wallNormal.z, -wallNormal.dot(wallPoint));
    }

    std::vector<Vec2> ShadowObject::ComputeConvexHull(std::vector<Vec2> vertices)
    {
        std::vector<Vec2> hull;
        if (vertices.size() < 3) return hull; //3未満なら凸包計算不可

        BubbleSort(vertices); // Z → Y の順でソート

        for (const auto& v : vertices)
        {
            while (hull.size() >= 2 && Cross(hull[hull.size() - 2], hull.back(), v) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(v);
        }

        for (int i = vertices.size() - 1; i >= 0; i--)
        {
            while (hull.size() >= 2 && Cross(hull[hull.size() - 2], hull.back(), vertices[i]) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(vertices[i]);
        }

        return hull;
    }

    void ShadowObject::CreatePolygonMesh(const std::vector<Vec2>& vertices)
    {
        if (vertices.size() < 3)
        {
            std::cerr << "Not enough vertices to create a polygon!" << std::endl;
            return;
        }

        std::vector<VertexPositionColor> meshVertices;
        Col4 color(0.0f, 0.0f, 0.0f, 1.0f);

        for (const auto& vertex : vertices)
        {
            Vec3 v(vertex.x, vertex.y, 0.0f);
            meshVertices.push_back(VertexPositionColor(v, color));
        }

        std::vector<uint16_t> indices;
        for (size_t i = 0; i < vertices.size() - 2; ++i)
        {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }

        m_drawComp->CreateOriginalMesh(meshVertices, indices);
    }

    std::vector<Vec3> ShadowObject::GetBoxVertices()
    {
        std::vector<Vec3> boxVertices;

        auto box = GetStage()->GetSharedGameObject<Box>(L"Box");
        if (!box)
        {
            std::cerr << "Box object not found!" << std::endl;
            return boxVertices;
        }

        auto boxTransform = box->GetComponent<Transform>();
        Vec3 position = boxTransform->GetPosition();
        Vec3 scale = boxTransform->GetScale();

        boxVertices = {
            position + Vec3(-scale.x / 2, -scale.y / 2, -scale.z / 2),
            position + Vec3(scale.x / 2, -scale.y / 2, -scale.z / 2),
            position + Vec3(-scale.x / 2, scale.y / 2, -scale.z / 2),
            position + Vec3(scale.x / 2, scale.y / 2, -scale.z / 2),
            position + Vec3(-scale.x / 2, -scale.y / 2, scale.z / 2),
            position + Vec3(scale.x / 2, -scale.y / 2, scale.z / 2),
            position + Vec3(-scale.x / 2, scale.y / 2, scale.z / 2),
            position + Vec3(scale.x / 2, scale.y / 2, scale.z / 2)
        };

        return boxVertices;
    }

    float ShadowObject::Cross(const Vec2& a, const Vec2& b, const Vec2& c)
    {
        Vec2 ab = b - a;
        Vec2 ac = c - a;

        return ab.x * ac.y - ab.y * ac.x; //Z-Y 平面の判定
    }

    void ShadowObject::BubbleSort(std::vector<Vec2>& vertices)
    {
        for (size_t i = 0; i < vertices.size() - 1; ++i)
        {
            for (size_t j = 0; j < vertices.size() - i - 1; ++j)
            {
                if (vertices[j].x > vertices[j + 1].x ||
                    (vertices[j].x == vertices[j + 1].x && vertices[j].y > vertices[j + 1].y))
                {
                    std::swap(vertices[j], vertices[j + 1]);
                }
            }
        }
    }
}