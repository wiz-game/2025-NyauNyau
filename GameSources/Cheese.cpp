/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//構築と破壊
	Cheese::Cheese(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	Cheese::~Cheese() {}


	void Cheese::OnCreate()
	{
		//ドローコンポーネントの追加と設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//drawComp->SetTextureResource(L" ");
		drawComp->SetBlendState(BlendState::Additive);//加算合成
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		drawComp->SetDiffuse(Col4(1.0f, 0.0f, 1.0f, 1.0f));//マテリアルの拡散反射の色を設定
		drawComp->SetEmissive(Col4(1.0f, 0.0f, 1.0f, 1.0f));

		//トランスフォームコンポーネントの取得と設定
		m_transComp = GetComponent<Transform>();
		m_transComp->SetScale(m_Scale);
		m_transComp->SetPosition(m_Position);
		//タグ
		AddTag(L"Cheese");


	}
	//void Cheese::OnUpdate()
	//{
	//	//ビルボード処理
	//	auto stage = GetStage();
	//	auto camera = stage->GetView()->GetTargetCamera();
	//	auto viewAatrix = camera->GetViewMatrix(); //ビュー行列を取得
	//	Quat viewQuat(viewAatrix);//ビュー行列からクォータニオン(四元数)を作成
	//	viewQuat.x *= -1.0f;
	//	viewQuat.y *= -1.0f;
	//	viewQuat.z *= -1.0f;
	//	m_transComp->SetQuaternion(viewQuat);
	//}


}
//end basecross
