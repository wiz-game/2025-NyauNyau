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
        m_drawComp->SetMeshResource(L"DEFAULT_CUBE");
        m_drawComp->SetDiffuse(Col4(0, 0, 0, 1));
        m_drawComp->SetEmissive(Col4(0.2, 0.2, 0.2, 1));
    }

    void ShadowObject::OnUpdate()
    {
        auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        m_lightPos = light->GetComponent<Transform>()->GetPosition();

        auto boxObj = GetStage()->GetSharedGameObject<Box>(L"Box");
        Vec3 boxObjPos = boxObj->GetComponent<Transform>()->GetPosition();

        auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        Vec3 wallNormal = wall->GetWallNormal();
        Vec3 wallPoint = wall->GetWallPosition();

        //Vec4 wallPlane = GeneratePlane(wallPoint, wallNormal);
        //std::vector<Vec3> shadowIntersections = ComputeShadowIntersections(wallPlane, m_lightPos, GetBoxVertices());

        // 影ポリゴンの形状を整理（凸包適用）
       /* std::vector<Vec2> projectedVertices;
        for (const auto& vertex : shadowIntersections)
        {
            projectedVertices.push_back(Vec2(vertex.x, vertex.y));
        }
        m_shadowVertices = ComputeConvexHull(projectedVertices);*/

        // `XMMatrixShadow` を使用して影を描画
        auto wallPointVec = XMVectorSet(wallPoint.x, wallPoint.y, wallPoint.z, 0.0f);
        auto wallNormalVec = XMVectorSet(wallNormal.x, wallNormal.y, wallNormal.z, 0.0f);

        // 平面を生成
        auto plane = XMPlaneFromPointNormal(wallPointVec, wallNormalVec);

        auto shadowMatrix = XMMatrixShadow(plane, XMVectorSet(m_lightPos.x, m_lightPos.y, m_lightPos.z, 1.0f) * -1);

        Mat4x4 shadowMat4x4(shadowMatrix);
        m_drawComp->SetMeshToTransformMatrix(shadowMat4x4);
    }

    std::vector<Vec3> ShadowObject::GetBoxVertices()
    {
        std::vector<Vec3> boxVertices;

        auto box = GetStage()->GetSharedGameObject<Box>(L"Box");
        if (!box)
        {
            std::cerr << "Box object not found!" << std::endl;
            return boxVertices; // 空のリストを返す
        }

        auto boxTransform = box->GetComponent<Transform>();
        Vec3 position = boxTransform->GetPosition();
        Vec3 scale = boxTransform->GetScale();

        // **Boxの各頂点を計算**
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

    /*std::vector<Vec3> ShadowObject::ComputeShadowIntersections(const Vec4& plane, const Vec3& lightPos, const std::vector<Vec3>& vertices)
    {
        std::vector<Vec3> intersections;
        for (const auto& vertex : vertices)
        {
            Vec3 lightDir = Vec3(vertex - lightPos).normalize();
            float denominator = plane.x * lightDir.x + plane.y * lightDir.y + plane.z * lightDir.z;

            if (fabs(denominator) < 1e-6f) continue;

            float t = -(plane.x * lightPos.x + plane.y * lightPos.y + plane.z * lightPos.z + plane.w) / denominator;
            intersections.push_back(lightPos + lightDir * t);
        }
        return intersections;
    }*/

    /*std::vector<Vec2> ShadowObject::ComputeConvexHull(const std::vector<Vec2>& vertices)
    {
        std::vector<Vec2> hull;
        if (vertices.size() < 3) return vertices;

        std::sort(vertices.begin(), vertices.end(), [](const Vec2& a, const Vec2& b) { return a.x < b.x; });

        std::vector<Vec2> lower, upper;
        for (const auto& v : vertices)
        {
            while (lower.size() >= 2 && Cross(lower[lower.size() - 2], lower.back(), v) <= 0)
            {
                lower.pop_back();
            }
            lower.push_back(v);
        }
        for (size_t i = vertices.size() - 1; i >= 0; --i)
        {
            while (upper.size() >= 2 && Cross(upper[upper.size() - 2], upper.back(), vertices[i]) <= 0)
            {
                upper.pop_back();
            }
            upper.push_back(vertices[i]);
        }
        lower.pop_back();
        upper.pop_back();
        hull.insert(hull.end(), lower.begin(), lower.end());
        hull.insert(hull.end(), upper.begin(), upper.end());

        return hull;
    }*/

    Vec4 ShadowObject::GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal)
    {
        return Vec4(wallNormal.x, wallNormal.y, wallNormal.z, -wallNormal.dot(wallPoint));
    }

    float ShadowObject::Cross(const Vec2& a, const Vec2& b, const Vec2& c)
    {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
}