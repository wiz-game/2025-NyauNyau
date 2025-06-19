// BoxShadowStrategy.cpp

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
        // GameObject が Box 型にキャスト可能か確認
        auto box = std::dynamic_pointer_cast<Box>(obj);
        if (box)
        {
            // トランスフォームコンポーネントを取得し、ワールド変換行列を得る
            auto transform = box->GetComponent<Transform>();
            Mat4x4 worldMatrix = transform->GetWorldMatrix();

            // Box のローカル空間の頂点を取得
            std::vector<Vec3> localVertices = box->GetBoxVertices();
            std::vector<Vec3> worldVertices;
            worldVertices.reserve(localVertices.size());

            // ローカル頂点をワールド空間に変換
            for (const auto& v : localVertices) {
                worldVertices.push_back(v * worldMatrix);
            }

            // 影の交点（壁との交差点）を計算
            std::vector<Vec3> shadowVertices = ComputeShadowIntersections(lightPos, worldVertices);

            // 凸包アルゴリズムで影の輪郭を整理して返す
            return ComputeConvexHull(shadowVertices);
        }

        // Box 型でない GameObject の場合は影を生成しない
        return {};
    }

    // 光源とオブジェクトの各頂点の直線を壁の面と交差させ、交点を計算する
    std::vector<Vec3> BoxShadowStrategy::ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& objectVertices)
    {
        std::vector<Vec3> intersections;

        // 壁オブジェクトの取得
        auto wallObj = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        if (!wallObj) return intersections;

        // 壁のトランスフォームとワールド行列の取得
        auto wallTransform = wallObj->GetComponent<Transform>();
        Mat4x4 wallWorldMatrix = wallTransform->GetWorldMatrix();

        // 壁の中心位置とスケールを取得
        Vec3 wallCenterPos = Vec3(wallWorldMatrix._41, wallWorldMatrix._42, wallWorldMatrix._43);
        Vec3 wallScale = wallTransform->GetScale();

        // 壁の法線（Z軸方向）をワールド空間から取得し正規化
        Vec3 wallNormal = Vec3(wallWorldMatrix._31, wallWorldMatrix._32, wallWorldMatrix._33);
        wallNormal.normalize();

        // 壁の表面上にある一点を法線方向から計算
        Vec3 wallSurfacePoint = wallCenterPos - wallNormal * wallScale.z;

        // 壁の表面を定義する平面を生成（Ax + By + Cz + D = 0 形式）
        Vec4 wallPlane = GeneratePlane(wallSurfacePoint, wallNormal);

        // 各頂点に対して光源との直線を壁面と交差させる
        for (const auto& vertex : objectVertices)
        {
            Vec3 rayDirection = vertex - lightPos;
            float denominator = wallNormal.dot(rayDirection);

            // 壁面と平行な場合はスキップ
            if (fabs(denominator) < 1e-6f) {
                continue;
            }

            // 交点パラメータ t を計算（光線のスケーリング係数）
            float numerator = -(wallNormal.dot(lightPos) + wallPlane.w);
            float t = numerator / denominator;

            // t が 1.0 未満なら、影として使う意味がない（物体の裏側など）
            if (t < 1.0f) {
                continue;
            }

            // 壁表面との交点を計算
            Vec3 intersection = lightPos + rayDirection * t;

            // Z座標の補正は不要になったので削除済み

            Vec3 intersection = lightPos + rayDirection * t;
            intersections.push_back(intersection);
        }

        return intersections;
    }

    // 指定された点と法線から、平面方程式 (A,B,C,D) を生成する
    Vec4 BoxShadowStrategy::GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal)
    {
        // D = -n・p を使って Vec4 に格納
        return Vec4(wallNormal.x, wallNormal.y, wallNormal.z, wallNormal.dot(wallPoint));
    }

    // 入力された頂点群から凸包（影の輪郭）を計算する
    std::vector<Vec3> BoxShadowStrategy::ComputeConvexHull(std::vector<Vec3> vertices)
    {
        if (vertices.size() < 3) {
            return vertices; // 凸包を構成できない場合はそのまま返す
        }

        // X-Y 座標でソート（Y優先でもOKだが今回はX優先）
        std::sort(vertices.begin(), vertices.end(), [](const Vec3& a, const Vec3& b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
            });

        // 同一のXY座標を持つ点を削除して冗長性を減らす
        vertices.erase(std::unique(vertices.begin(), vertices.end(), [](const Vec3& a, const Vec3& b) {
            return a.x == b.x && a.y == b.y;
            }), vertices.end());

        if (vertices.size() < 3) {
            return vertices;
        }

        // Graham scan 法に近いアルゴリズムで凸包の上下辺を構築
        std::vector<Vec3> lower_hull;
        std::vector<Vec3> upper_hull;

        for (const auto& p : vertices) {
            // 下側凸包構築
            while (lower_hull.size() >= 2 && Cross(lower_hull[lower_hull.size() - 2], lower_hull.back(), p).z <= 0) {
                lower_hull.pop_back();
            }
            lower_hull.push_back(p);

            // 上側凸包構築
            while (upper_hull.size() >= 2 && Cross(upper_hull[upper_hull.size() - 2], upper_hull.back(), p).z >= 0) {
                upper_hull.pop_back();
            }
            upper_hull.push_back(p);
        }

        // 上下を結合して凸包を完成（重複点を除いて結合）
        std::vector<Vec3> convex_hull = lower_hull;
        for (size_t i = upper_hull.size() - 2; i > 0; --i) {
            convex_hull.push_back(upper_hull[i]);
        }
        return convex_hull;
    }
}