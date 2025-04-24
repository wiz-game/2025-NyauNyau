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
		static float rotate = 0.0f;

		auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight"); //ライトを取得
		m_lightPos = light->GetComponent<Transform>()->GetPosition();

		auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
		Vec3 wallNormal = wall->GetWallNormal();
		Vec3 wallPoint = wall->GetWallPosition();
		
		Mat4x4 matrix;
		matrix.affineTransformation(Vec3(1), Vec3(0), Vec3(rotate, rotate, rotate), Vec3(0)); // 拡大・回転行列を作成
		auto wallPointVec  = XMVectorSet(wallPoint.x+0.001, wallPoint.y, wallPoint.z, 0.0f);//DirectXのVecterに変換
		auto wallNormalVec = XMVectorSet(wallNormal.x, wallNormal.y, wallNormal.z, 0.0f);//DirectXのVecterに変換
		//auto light = XMVectorSet(-4.0f, 0.0f, 0.0f, 0.0f); // 影を映すライトの想定位置
		//auto wallPointVec = XMVectorSet (-5.299f, 4.0f, 0.0f, 0.0f);//DirectXのVecterに変換
		//auto wallNormalVec = XMVectorSet(-1.0f,0.0f, 0.0f, 0.0f);//DirectXのVecterに変換
		//auto plane = XMPlaneFromPointNormal(wallPointVec, wallNormalVec); // 平面上の1点と、その平面の向きから「平面」を作る
		auto plane = XMPlaneFromPointNormal(wallPointVec, wallNormal);
		auto shadowMatrix = XMMatrixShadow(plane, m_lightPos*-1); // 射影行列を作成
		Mat4x4 shadowMat4x4(shadowMatrix); // BaseCrossの行列(Mat4x4)に変換

		

		// ドローコンポーネントに行列を適用する
		m_drawComp->SetMeshToTransformMatrix(matrix * shadowMat4x4);

		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(XMVectorGetX(wallNormalVec), 6, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Y=" + Util::FloatToWStr(XMVectorGetY(wallNormalVec), 6, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Z=" + Util::FloatToWStr(XMVectorGetZ(wallNormalVec), 6, Util::FloatModify::Fixed) + L"\n";


		wstring str = positionStr;


		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}
}