#include "stdafx.h"
#include "Project.h"
#include "BoxShadowStrategy.h"
#include "BaseShadowStrategy.h"
#include "RaycastLine.h"

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
            auto transform = box->GetComponent<Transform>();
            Mat4x4 worldMatrix = transform->GetWorldMatrix();

            std::vector<Vec3> localVertices = box->GetBoxVertices();
            std::vector<Vec3> worldVertices;
            worldVertices.reserve(localVertices.size());

            for (const auto& v : localVertices) {
                worldVertices.push_back(v * worldMatrix);
            }

            // 影の交点を計算
            std::vector<Vec3> shadowVertices = ComputeShadowIntersections(lightPos, worldVertices);

            // 凸包を計算して影の形状を整理
            return ComputeConvexHull(shadowVertices);
        }

        return {}; // `GameObject` が `Box` でない場合、影を計算しない
    }

    std::vector<Vec3> BoxShadowStrategy::ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& objectVertices)
    {
        std::vector<Vec3> intersections;

        // === 1. 壁の「表面」の平面を、ワールド行列から正確に計算 ===
        auto wallObj = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        if (!wallObj) return intersections;

        auto wallTransform = wallObj->GetComponent<Transform>();
        Mat4x4 wallWorldMatrix = wallTransform->GetWorldMatrix();

        Vec3 wallCenterPos = Vec3(wallWorldMatrix._41, wallWorldMatrix._42, wallWorldMatrix._43);
        Vec3 wallScale = wallTransform->GetScale();
        Vec3 wallNormal = -Vec3(wallWorldMatrix._31, wallWorldMatrix._32, wallWorldMatrix._33);
        wallNormal.normalize();

        // 壁の「表面」上の一点を計算
        Vec3 wallSurfacePoint = wallCenterPos - wallNormal * wallScale.z ;

        // この表面の位置と法線から、正しい平面の方程式を生成
        Vec4 wallPlane = GeneratePlane(wallSurfacePoint, wallNormal); // GeneratePlaneは D = -n・p を使う


        // === 2. 交点計算ループ ===
        for (const auto& vertex : objectVertices)
        {
            Vec3 rayDirection = vertex - lightPos;
            float denominator = wallNormal.dot(rayDirection);

            if (fabs(denominator) < 1e-6f) {
                continue;
            }

            float numerator = -(wallNormal.dot(lightPos) + wallPlane.w);
            float t = numerator / denominator;

            if (t < 1.0f) {
                continue;
            }

            // 計算された交点は、すでに正しい壁の表面上にある
            Vec3 intersection = lightPos + rayDirection * t;

            // ★★★ Z座標の強制的な上書きは、もはや不要！ ★★★
            // intersection.z = wallPoint.z; // ← この行は削除する

            intersections.push_back(intersection);
        }

        return intersections;
    }


    Vec4 BoxShadowStrategy::GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal)
    {
        return Vec4(wallNormal.x, wallNormal.y, wallNormal.z, wallNormal.dot(wallPoint));
    }

    std::vector<Vec3> BoxShadowStrategy::ComputeConvexHull(std::vector<Vec3> vertices)
    {
        if (vertices.size() < 3) {
            return vertices; // 頂点が3未満なら、それがそのまま凸包
        }

        // X-Y座標でソート
        std::sort(vertices.begin(), vertices.end(), [](const Vec3& a, const Vec3& b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
            });

        // 重複点を削除すると、より安定する
        vertices.erase(std::unique(vertices.begin(), vertices.end(), [](const Vec3& a, const Vec3& b) {
            return a.x == b.x && a.y == b.y; // XYが同じなら重複とみなす
            }), vertices.end());

        if (vertices.size() < 3) {
            return vertices; // 重複削除後に3未満になった場合
        }


        // 上側と下側の凸包を計算
        std::vector<Vec3> lower_hull;
        std::vector<Vec3> upper_hull;

        for (const auto& p : vertices) {
            // 下側凸包
            while (lower_hull.size() >= 2 && Cross(lower_hull[lower_hull.size() - 2], lower_hull.back(), p).z <= 0) {
                lower_hull.pop_back();
            }
            lower_hull.push_back(p);

            // 上側凸包
            while (upper_hull.size() >= 2 && Cross(upper_hull[upper_hull.size() - 2], upper_hull.back(), p).z >= 0) {
                upper_hull.pop_back();
            }
            upper_hull.push_back(p);
        }

        // 上側と下側を結合して、最終的な凸包を作成
        std::vector<Vec3> convex_hull = lower_hull;
        // 上側は逆順に追加する（最後の点と最初の点は重複するので除く）
        for (size_t i = upper_hull.size() - 2; i > 0; --i) {
            convex_hull.push_back(upper_hull[i]);
        }

        return convex_hull;
    }
}