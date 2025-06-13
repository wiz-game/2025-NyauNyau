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

        auto box = std::dynamic_pointer_cast<Box>(obj);
        if (!box) return {};
        Mat4x4 boxWorldMatrix = box->GetComponent<Transform>()->GetWorldMatrix();
        std::vector<Vec3> localVertices = box->GetBoxVertices();
        std::vector<Vec3> worldVertices;
        worldVertices.reserve(localVertices.size());
        for (const auto& v : localVertices) {
            worldVertices.push_back(v * boxWorldMatrix);
        }

        // --- 2. ★★★ 裏面頂点をカリング（選別）する ★★★ ---
        std::vector<Vec3> silhouetteVertices;

        // 物体の中心をワールド座標で取得
        Vec3 boxCenter = Vec3(boxWorldMatrix._41, boxWorldMatrix._42, boxWorldMatrix._43);

        for (const auto& vertex : worldVertices)
        {
            // 頂点から中心へ向かう法線的なベクトル (簡単化のため正規化)
            Vec3 normal_ish = Vec3(boxCenter - vertex).normalize();
            // 頂点から光源へ向かうベクトル (正規化)
            Vec3 toLight = Vec3(lightPos - vertex).normalize();

            // 2つのベクトルの内積をチェック
            // 内積がプラスなら、光源はその頂点の「表側」から照らしている
            if (normal_ish.dot(toLight) > 0)
            {
                silhouetteVertices.push_back(vertex);
            }
        }

        // もし全ての頂点が裏側なら、影はできない
        if (silhouetteVertices.empty()) {
            return {};
        }

        // --- 3. フィルタリング後の頂点を使って計算 ---
        std::vector<Vec3> shadowVertices = ComputeShadowIntersections(lightPos, silhouetteVertices);

        return ComputeConvexHull(shadowVertices);
    }

    std::vector<Vec3> BoxShadowStrategy::ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& objectVertices)
    {
        std::vector<Vec3> intersections;

        // === 1. 壁の「表面」の平面を、Transformから正確に計算 ===
        auto wallObj = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        if (!wallObj) return intersections;

        auto wallTransform = wallObj->GetComponent<Transform>();
        Mat4x4 wallWorldMatrix = wallTransform->GetWorldMatrix();

        // 壁の中心座標とスケールを取得
        Vec3 wallCenterPos = Vec3(wallWorldMatrix._41, wallWorldMatrix._42, wallWorldMatrix._43);
        Vec3 wallScale = wallTransform->GetScale();

        // 壁の法線ベクトル（手前を向く法線）
        Vec3 wallNormal = -Vec3(wallWorldMatrix._31, wallWorldMatrix._32, wallWorldMatrix._33);
        wallNormal.normalize();

        // ★★★ これが最も重要な計算 ★★★
        // 壁の「表面」上の一点を計算する
        // 中心の位置から、法線と逆方向（壁の内部方向）に、厚みの半分だけ移動する
        Vec3 wallSurfacePoint = wallCenterPos - wallNormal * (wallScale.z / 2.0f);

        // この表面の位置と法線から、正しい平面の方程式を生成
        Vec4 wallPlane = GeneratePlane(wallSurfacePoint, wallNormal); // D = -n・p


        // === 2. 交点計算（ここは変更なし） ===
        for (const auto& vertex : objectVertices)
        {
            Vec3 rayDirection = vertex - lightPos;
            float denominator = wallNormal.dot(rayDirection);
            if (fabs(denominator) < 1e-6f) continue;

            float distance_to_plane = wallNormal.dot(wallSurfacePoint - lightPos);
            float t = distance_to_plane / denominator;

            if (t < 1.0f) continue; // 物体の後ろにできる影のみ対象

            Vec3 intersection = lightPos + rayDirection * t;
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