/*!
@file ShadowObject.h
@brief 影の算出・描画を行うオブジェクト（CUBE限定）
*/

#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowObject.h"

namespace basecross
{
    void ShadowObject::OnCreate()
    {
        m_drawComp = AddComponent<PCStaticDraw>();
        m_drawComp->SetOriginalMeshUse(true);

        //m_drawComp->SetMeshResource(L"DEFAULT_CUBE");
        //m_drawComp->SetDiffuse(Col4(0, 0, 0, 1));
        //m_drawComp->SetEmissive(Col4(0.2, 0.2, 0.2, 1));
        //ptrDraw->CreateOriginalMesh(vertices, indices);
    }

    void ShadowObject::OnUpdate()
    {
        auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        m_lightPos = light->GetComponent<Transform>()->GetPosition();

        auto boxVertices = GetBoxVertices();

        auto shadowIntersections = ComputeShadowIntersections(m_lightPos, boxVertices);

        // 最も外側の交点を求める（凸包アルゴリズムを適用）
        std::vector<Vec2> projectedVertices;
        for (const auto& vertex : shadowIntersections)
        {
            projectedVertices.push_back(Vec2(vertex.x, vertex.y));
        }
        m_shadowVertices = ComputeConvexHull(projectedVertices);

        // 影ポリゴンを生成
        CreatePolygonMesh(m_shadowVertices);
    }

    // 光源とボックスの頂点を線で結び、その延長線を壁まで伸ばし交点を取得
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

            float denominator = wallPlane.x * lightDir.x + wallPlane.y * lightDir.y + wallPlane.z * lightDir.z;

            if (fabs(denominator) < 1e-6f)
                continue;

            float t = -(wallPlane.x * lightPos.x + wallPlane.y * lightPos.y + wallPlane.z * lightPos.z + wallPlane.w) / denominator;

            intersections.push_back(lightPos + lightDir * t);
        }

        return intersections;
    }

    // 壁平面の方程式を生成
    Vec4 ShadowObject::GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal)
    {
        return Vec4(wallNormal.x, wallNormal.y, wallNormal.z, -wallNormal.dot(wallPoint));
    }

    // 交点の凸包を計算（影の形状を整理）
    std::vector<Vec2> ShadowObject::ComputeConvexHull(std::vector<Vec2> vertices)
    {
        std::vector<Vec2> hull;
        if (vertices.size() < 3) return hull; // 3点未満なら凸包は作れない

        // バブルソートで座標を昇順に整理
        BubbleSort(vertices);

        // 下部凸包
        for (const auto& v : vertices)
        {
            while (hull.size() >= 2 && Cross(hull[hull.size() - 2], hull.back(), v) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(v);
        }

        // 上部凸包
        size_t hull_size = hull.size();
        for (int i = vertices.size() - 2; i >= 0; i--)
        {
            while (hull.size() > hull_size && Cross(hull[hull.size() - 2], hull.back(), vertices[i]) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(vertices[i]);
        }

        hull.pop_back(); // 始点を削除
        return hull;
    }


    // 影ポリゴンを生成
    void ShadowObject::CreatePolygonMesh(const std::vector<Vec2>& vertices)
    {
        if (vertices.empty()) return;

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
        //m_drawComp->SetOriginalMeshUse(true);
    }

    // Boxの頂点を取得
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

    // ベクトルの外積を計算（2D版）
    float ShadowObject::Cross(const Vec2& a, const Vec2& b, const Vec2& c)
    {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    //バブルソート
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