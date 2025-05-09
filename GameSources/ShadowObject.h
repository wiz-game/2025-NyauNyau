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

        // Boxの頂点を取得
        std::vector<Vec3> GetBoxVertices();

        // 光源とボックスの頂点を線で結び、その延長線を壁まで伸ばし交点を取得
        std::vector<Vec3> ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& boxVertices);

        // 壁平面の方程式を生成
        Vec4 GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal);

        // 交点の凸包を計算（影の形状を整理）
        std::vector<Vec2> ComputeConvexHull(std::vector<Vec2> vertices);

        // 影ポリゴンを生成
        void CreatePolygonMesh(const std::vector<Vec2>& vertices);

        // ベクトルの外積を計算（2D版）
        float Cross(const Vec2& a, const Vec2& b, const Vec2& c);

        //バブルソート
        void BubbleSort(std::vector<Vec2>& points);
        virtual void OnCreate() override;
        virtual void OnUpdate() override;
    };
}