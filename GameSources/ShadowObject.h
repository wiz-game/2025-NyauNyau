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
        std::vector<Vec3> m_shadowVertices; //影のポリゴン頂点  

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

        //交点の凸包を計算  
        std::vector<Vec3> ComputeConvexHull(std::vector<Vec3> vertices);

        //影ポリゴンを生成  
        void CreatePolygonMesh(const std::vector<Vec3>& vertices);

        //交点を回転させる
        //Vec3 RotateVertex(const Vec3& vertex, const Vec3& rotation);

        //ベクトルの外積を計算
        Vec3 Cross(const Vec3& a, const Vec3& b, const Vec3& c);

        //バブルソート  
        void BubbleSort(std::vector<Vec3>& vertices);

        void DrawStrings();


        vector<Vec3> GetVertices() const;


        virtual void OnCreate() override;
        virtual void OnUpdate() override;
    };
}