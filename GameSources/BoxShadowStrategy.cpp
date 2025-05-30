#pragma once
#include "stdafx.h"
#include "Project.h"
#include "BoxShadowStrategy.h"

namespace basecross
{
    std::vector<Vec3> BoxShadowStrategy::GetBoxVertices()
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
        position = Vec3(position.x, position.y, -position.z);
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

    std::vector<Vec3> BoxShadowStrategy::ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& vertices)
    {
        std::vector<Vec3> shadowVertices;
        for (const auto& vertex : vertices)
        {
            Vec3 shadowDir = Vec3(vertex - lightPos).normalize();
            Vec3 shadowVertex = vertex + shadowDir * 0.5f; // ‰e‚ðŠg’£
            shadowVertices.push_back(shadowVertex);
        }
        return shadowVertices;
    }
    std::vector<Vec3> BoxShadowStrategy::ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& objectVertices)
    {
        std::vector<Vec3> shadowVertices = ComputeShadowIntersections(lightPos, objectVertices);
        return ComputeConvexHull(shadowVertices);
    }

    std::vector<Vec3> BoxShadowStrategy::ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& objectVertices)
    {
        std::vector<Vec3> intersections;

        auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        if (!wall)
            return intersections;

        Vec3 wallNormal = wall->GetWallNormal();
        Vec3 wallPoint = wall->GetWallPosition();
        Vec4 wallPlane = GeneratePlane(wallPoint, wallNormal);

        for (const auto& vertex : objectVertices)
        {
            Vec3 lightDir = Vec3(vertex - lightPos).normalize();

            float denominator = wallPlane.x * lightDir.x + wallPlane.y * lightDir.y + wallPlane.z * lightDir.z;
            if (fabs(denominator) < 1e-6f)
                continue;

            float t = -(wallPlane.x * lightPos.x + wallPlane.y * lightPos.y + wallPlane.z * lightPos.z + wallPlane.w) / denominator;
            if (t < 0)
                continue;

            Vec3 intersection = lightPos + lightDir * t;

            intersection.x = wallPoint.x; // •Ç‚ÌˆÊ’u‚É‰e‚ðŒÅ’è

            intersections.push_back(intersection);
        }

        return intersections;
    }

    Vec4 BoxShadowStrategy::GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal)
    {
        return Vec4(wallNormal.x, wallNormal.y, wallNormal.z, -wallNormal.dot(wallPoint));
    }

   std::vector<Vec3> BoxShadowStrategy::ComputeConvexHull(std::vector<Vec3> vertices)
    {
        std::vector<Vec3> hull;
        if (vertices.size() < 3) return hull;

        BubbleSort(vertices);

        for (const auto& v : vertices)
        {
            while (hull.size() >= 2 && Cross(hull[hull.size() - 2], hull.back(), v).z <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(v);
        }

        for (int i = vertices.size() - 1; i >= 0; i--)
        {
            while (hull.size() >= 2 && Cross(hull[hull.size() - 2], hull.back(), vertices[i]).z <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(vertices[i]);
        }

        return hull;
    }

    
}