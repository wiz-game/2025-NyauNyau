/*!
@file ShadowObject.h
@brief 影の算出・描画を行うオブジェクト
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

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(32.0f, 32.0f, 640.0f, 480.0f));

	}

    void ShadowObject::OnUpdate()
    {
        static float rotate = 0.0f; // 回転

        // ライトの位置を取得
        auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        Vec3 lightPos = light->GetComponent<Transform>()->GetPosition();

        // 壁の情報を取得
        auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        Vec3 wallNormal = wall->GetWallNormal();
        Vec3 wallPoint = wall->GetWallPosition();

        //オブジェクトの位置情報の取得
        auto boxObj = GetStage()->GetSharedGameObject<Box>(L"Box");
        Vec3 boxObjPos = boxObj->GetComponent<Transform>()->GetPosition();

        // **影の倍率を動的に計算**
        float shadowScale = CalculateShadowScale(lightPos, boxObjPos, wallPoint, wallNormal);

        // **オブジェクトの動きに応じて影の位置を更新**
        Vec3 lightDirection = Vec3(boxObjPos - lightPos).normalize();
        float t = ((wallPoint - lightPos).dot(wallNormal)) / (lightDirection.dot(wallNormal));
        Vec3 shadowPosition = lightPos + lightDirection * t;

        // **影の行列を適用**
        Mat4x4 matrix;
        matrix.affineTransformation(Vec3(shadowScale), Vec3(0), Vec3(rotate, rotate, rotate), shadowPosition);

        // 射影行列を適用（光源と影の関係を考慮）
        auto wallPointVec = XMVectorSet(wallPoint.x, wallPoint.y, wallPoint.z, 0.0f);
        auto wallNormalVec = XMVectorSet(wallNormal.x, wallNormal.y, wallNormal.z, 0.0f);
        auto plane = XMPlaneFromPointNormal(wallPointVec, wallNormalVec);
        auto shadowMatrix = XMMatrixShadow(plane, lightPos * -1);

        Mat4x4 shadowMat4x4(shadowMatrix);

        // **影の行列をオブジェクトに適用**
        m_drawComp->SetMeshToTransformMatrix(matrix * shadowMat4x4);
    }

    float  ShadowObject::CalculateShadowScale(const Vec3& lightPos, const Vec3& objectPos, const Vec3& wallPoint, const Vec3& wallNormal)
    {
        // 光源がオブジェクトより低い場合、影の倍率は 1.0f にする（影が正しく生成されない）
        if (lightPos.y <= objectPos.y) {
            return 1.0f;
        }

        // 光源とオブジェクトの距離を計算
        float objectDistance = (objectPos - lightPos).length();

        // 光線の方向（光源 → オブジェクトの方向）
        Vec3 lightDirection = Vec3(objectPos - lightPos).normalize();

        // 壁との交点を求める（光線の方向と壁の法線を用いた計算）
        float t = ((wallPoint - lightPos).dot(wallNormal)) / (lightDirection.dot(wallNormal));

        // 壁に投影された影の位置を求める
        Vec3 shadowPoint = lightPos + lightDirection * t;

        // 影の長さを計算（オブジェクトから影の投影点まで）
        float shadowLength = Vec3(shadowPoint - objectPos).length();

        // 影の倍率を計算（影の長さ / 光源とオブジェクトの距離）
        float shadowScale = shadowLength / objectDistance;

        return shadowScale;
    }
}
