#include "stdafx.h"
#include "Project.h"
#include "BoxShadowStrategy.h"
#include "BaseShadowStrategy.h"

namespace basecross
{
    // コンストラクタの実装
    BoxShadowStrategy::BoxShadowStrategy(const std::shared_ptr<Stage>& stagePtr)
        : BaseShadowStrategy(stagePtr) // 基底クラスのコンストラクタを呼び出し
    {
    }


    std::vector<Vec3> BoxShadowStrategy::ComputeShadow(const Vec3& lightPos, const std::shared_ptr<GameObject>& obj)
    {
        // `GameObject` が `Box` なら、`GetBoxVertices()` を呼び出す
        auto box = std::dynamic_pointer_cast<Box>(obj);
        if (box)
        {
            std::vector<Vec3> objectVertices = box->GetBoxVertices();

            // 影の交点を計算
            std::vector<Vec3> shadowVertices = ComputeShadowIntersections(lightPos, objectVertices);

            // 凸包を計算して影の形状を整理
            return ComputeConvexHull(shadowVertices);
        }

        return {}; // `GameObject` が `Box` でない場合、影を計算しない
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
            intersection.x = wallPoint.x;

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