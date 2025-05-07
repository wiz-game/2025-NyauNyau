/*!
@file ShadowObject.h
@brief 影の算出・描画を行うオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
    class ShadowObject : public GameObject
    {
        std::shared_ptr<PCStaticDraw> m_drawComp; // 描画コンポーネント
        std::vector<Vec2> m_shadowVertices; // 影のポリゴン頂点

    public:
        Vec3 m_lightPos; // 光源の位置

        ShadowObject(const shared_ptr<Stage>& stage)
            : GameObject(stage), m_lightPos(0)
        {
        }

        virtual ~ShadowObject() {}

        // 影の倍率を求める関数
        //float CalculateShadowScale(const Vec3& lightPos, const Vec3& objectPos, const Vec3& wallPoint, const Vec3& wallNormal);

        // Boxの頂点を取得
        std::vector<Vec3> GetBoxVertices();

        // 交点を計算
        //std::vector<Vec3> ComputeShadowIntersections(const Vec4& plane, const Vec3& lightPos, const std::vector<Vec3>& vertices);

        // 影のポリゴンを生成（凸包適用）
        //std::vector<Vec2> ComputeConvexHull(const std::vector<Vec2>& vertices);

        // 壁の平面を作成
        Vec4 GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal);

        // 凸包計算用の外積関数
        float Cross(const Vec2& a, const Vec2& b, const Vec2& c);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
    };
}