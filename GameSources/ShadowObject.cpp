#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowObject.h"
#include "RaycastLine.h"

namespace basecross
{
    void ShadowObject::OnCreate()
    {
        m_drawComp = AddComponent<PCStaticDraw>();
        m_drawComp->SetOriginalMeshUse(true);
    }

    void ShadowObject::OnUpdate()
    {
        auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        m_lightPos = light->GetComponent<Transform>()->GetPosition();

        auto boxVertices = GetBoxVertices();
        auto shadowIntersections = ComputeShadowIntersections(m_lightPos, boxVertices);

        // 交点がない場合は処理を中断（強制終了を防止）
        if (shadowIntersections.empty())
        {
            std::cerr << "No intersections found! Skipping shadow generation." << std::endl;
            return;
        }

        // 最も外側の交点を求める（凸包アルゴリズムを適用）
        std::vector<Vec2> projectedVertices;
        for (const auto& vertex : shadowIntersections)
        {
            projectedVertices.push_back(Vec2(vertex.x, vertex.y));
        }
        m_shadowVertices = ComputeConvexHull(projectedVertices);

        // 影ポリゴンを生成
        CreatePolygonMesh(m_shadowVertices);

        // 光源から交点へのレイを生成（デバッグ用）
        for (const auto& intersection : shadowIntersections)
        {
            auto rayFromLight = GetStage()->AddGameObject<RaycastLine>();
            rayFromLight->SetLinePosition(m_lightPos, intersection);
        }
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
            // 光源からボックスの頂点へ向かうレイを生成
            Vec3 lightDir = Vec3(vertex - lightPos).normalize();

            float denominator = wallPlane.x * lightDir.x + wallPlane.y * lightDir.y + wallPlane.z * lightDir.z;
            if (fabs(denominator) < 1e-6f) // 壁と平行ならスキップ
                continue;

            float t = -(wallPlane.x * lightPos.x + wallPlane.y * lightPos.y + wallPlane.z * lightPos.z + wallPlane.w) / denominator;
            if (t < 0) // 交点が光源の後ろなら除外
                continue;

            // 交点を計算
            Vec3 intersection = lightPos + lightDir * t;

            if ((intersection - lightPos).length() < 1000.0f) // 有効範囲かチェック
            {
                intersections.push_back(intersection);
            }
        }

        // デバッグ出力：交点の数を確認
        std::cout << "Computed Intersections Count: " << intersections.size() << std::endl;

        if (intersections.empty()) {
            std::cerr << "No valid intersections found! Check wall positioning and light direction." << std::endl;
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
        if (vertices.size() < 3) return hull;

        BubbleSort(vertices);

        for (const auto& v : vertices)
        {
            while (hull.size() >= 2 && Cross(hull[hull.size() - 2], hull.back(), v) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(v);
        }

        size_t hull_size = hull.size();
        for (int i = vertices.size() - 2; i >= 0; i--)
        {
            while (hull.size() > hull_size && Cross(hull[hull.size() - 2], hull.back(), vertices[i]) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(vertices[i]);
        }

        hull.pop_back();
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
        for (size_t i = 1; i < vertices.size() - 1; ++i)
        {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        std::cout << "Created Indices Count: " << indices.size() << std::endl;

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
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    void ShadowObject::BubbleSort(std::vector<Vec2>& points)
    {
        size_t n = points.size();
        for (size_t i = 0; i < n - 1; ++i)
        {
            for (size_t j = 0; j < n - i - 1; ++j)
            {
                if (points[j].x > points[j + 1].x ||
                    (points[j].x == points[j + 1].x && points[j].y > points[j + 1].y))
                {
                    std::swap(points[j], points[j + 1]);
                }
            }
        }
    }
}