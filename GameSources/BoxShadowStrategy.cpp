#include "stdafx.h"
#include "Project.h"
#include "BoxShadowStrategy.h"
#include <algorithm> // for std::sort, std::unique

namespace basecross
{
    // コンストラクタ
    BoxShadowStrategy::BoxShadowStrategy(const std::shared_ptr<Stage>& stagePtr)
        : BaseShadowStrategy(stagePtr)
    {
    }

    // 影の頂点を計算するメインの処理
    std::vector<Vec3> BoxShadowStrategy::ComputeShadow(const Vec3& lightPos, const std::shared_ptr<GameObject>& obj)
    {
        // --- 1. Boxのワールド座標頂点を準備 ---
        auto box = std::dynamic_pointer_cast<Box>(obj);
        if (!box) return {};

        Mat4x4 boxWorldMatrix = box->GetComponent<Transform>()->GetWorldMatrix();
        std::vector<Vec3> localVertices = box->GetBoxVertices(); // (-0.5 to 0.5)のローカル頂点
        std::vector<Vec3> worldVertices;
        worldVertices.reserve(localVertices.size());
        for (const auto& v : localVertices) {
            worldVertices.push_back(v * boxWorldMatrix);
        }

        // --- 2. 光源から見て裏側にある頂点を計算から除外する（安定化のため） ---
        std::vector<Vec3> silhouetteVertices;
        Vec3 boxCenter = Vec3(boxWorldMatrix._41, boxWorldMatrix._42, boxWorldMatrix._43);

        for (const auto& vertex : worldVertices)
        {
            Vec3 normal_ish = Vec3(boxCenter - vertex).normalize();
            Vec3 toLight = Vec3(lightPos - vertex).normalize();
            if (normal_ish.dot(toLight) > 0) {
                silhouetteVertices.push_back(vertex);
            }
        }

        if (silhouetteVertices.empty()) return {};

        // --- 3. フィルタリング後の頂点で、壁との交点を計算 ---
        std::vector<Vec3> shadowVertices = ComputeShadowIntersections(lightPos, silhouetteVertices);

        // --- 4. 交点から凸包を計算して、最終的な影の形を返す ---
        return ComputeConvexHull(shadowVertices);
    }

    // レイと壁平面の交点を計算する
    std::vector<Vec3> BoxShadowStrategy::ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& objectVertices)
    {
        std::vector<Vec3> intersections;

        // --- 1. 壁の「表面」の平面を、ワールド行列から正確に計算 ---
        auto wallObj = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        if (!wallObj) return intersections;

        auto wallTransform = wallObj->GetComponent<Transform>();
        Mat4x4 wallWorldMatrix = wallTransform->GetWorldMatrix();

        Vec3 wallCenterPos = Vec3(wallWorldMatrix._41, wallWorldMatrix._42, wallWorldMatrix._43);
        Vec3 wallScale = wallTransform->GetScale();
        Vec3 wallNormal = -Vec3(wallWorldMatrix._31, wallWorldMatrix._32, wallWorldMatrix._33);
        wallNormal.normalize();

        Vec3 wallSurfacePoint = wallCenterPos - wallNormal * (wallScale.z / 2.0f);

        // ★★★ 正しい表面の点と法線から、正しい平面の方程式を生成 ★★★
        Vec4 wallPlane = GeneratePlane(wallSurfacePoint, wallNormal); // D = -n・p


        // === 2. 交点計算ループ ===
        for (const auto& vertex : objectVertices)
        {
            Vec3 rayDirection = vertex - lightPos;
            float denominator = wallNormal.dot(rayDirection);

            if (fabs(denominator) < 1e-6f) {
                continue;
            }

            // 分子 = -(光源の位置と平面の法線の内積 + D)
            float numerator = -(wallNormal.dot(lightPos) + wallPlane.w);

            // t を計算
            float t = numerator/denominator;


            // 物体の後ろ側にできる影のみを対象とする
            if (t < 1.0f) {
                continue;
            }

            Vec3 intersection = lightPos + rayDirection * t;
            intersections.push_back(intersection);
        }

        return intersections;
    }

    // 平面の方程式を生成する (D = -n・p)
    Vec4 BoxShadowStrategy::GeneratePlane(const Vec3& point, const Vec3& normal) const
    {
        return Vec4(normal.x, normal.y, normal.z, -normal.dot(point));
    }

    // 安定版の凸包計算アルゴリズム
    std::vector<Vec3> BoxShadowStrategy::ComputeConvexHull(std::vector<Vec3> vertices)
    {
        if (vertices.size() < 3) return vertices;
        std::sort(vertices.begin(), vertices.end(), [](const Vec3& a, const Vec3& b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
            });
        vertices.erase(std::unique(vertices.begin(), vertices.end(), [](const Vec3& a, const Vec3& b) {
            return a.x == b.x && a.y == b.y;
            }), vertices.end());
        if (vertices.size() < 3) return vertices;
        std::vector<Vec3> lower_hull, upper_hull;
        for (const auto& p : vertices) {
            while (lower_hull.size() >= 2) {
                Vec3 v1 = lower_hull.back() - lower_hull[lower_hull.size() - 2];
                Vec3 v2 = p - lower_hull[lower_hull.size() - 2];
                if (this->Cross(v1, v2).z <= 0) lower_hull.pop_back(); else break;
            }
            lower_hull.push_back(p);
            while (upper_hull.size() >= 2) {
                Vec3 v1 = upper_hull.back() - upper_hull[upper_hull.size() - 2];
                Vec3 v2 = p - upper_hull[upper_hull.size() - 2];
                if (this->Cross(v1, v2).z >= 0) upper_hull.pop_back(); else break;
            }
            upper_hull.push_back(p);
        }
        std::vector<Vec3> convex_hull = lower_hull;
        for (size_t i = 1; i < upper_hull.size() - 1; ++i) {
            convex_hull.push_back(upper_hull[upper_hull.size() - 1 - i]);
        }
        return convex_hull;
    }
}