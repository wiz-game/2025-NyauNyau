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
		m_drawComp->SetEmissive(Col4(0.5, 0.5, 0.5, 1));
	}

	void ShadowObject::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight"); //ライトを取得
		m_lightPos = light->GetComponent<Transform>()->GetPosition();

		static float rotate = 0.0f;

		Mat4x4 matrix;
		matrix.affineTransformation(Vec3(1), Vec3(0), Vec3(rotate, rotate, rotate), Vec3(0)); // 拡大・回転行列を作成
		auto wallPoint = XMVectorSet(0.0f, 0.0f, 2.f, 0.0f); // 平面の座標
		auto wallNormal = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f); // 平面の向き
		auto plane = XMPlaneFromPointNormal(wallPoint, wallNormal); // 平面上の1点と、その平面の向きから「平面」を作る
		auto light = XMVectorSet(0.0f, 0.0f, -3.0f, 1.0f); // 影を映すライトの想定位置
		auto shadowMatrix = XMMatrixShadow(plane, light); // 射影行列を作成
		Mat4x4 shadowMat4x4(shadowMatrix); // BaseCrossの行列(Mat4x4)に変換

		// ドローコンポーネントに行列を適用する
		m_drawComp->SetMeshToTransformMatrix(matrix * shadowMat4x4);
	}
}