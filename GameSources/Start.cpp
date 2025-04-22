
/*!
@file Character.cpp
@brief スタートの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//構築と破壊
	startGate::startGate(const shared_ptr<Stage>& StagePtr,
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
	startGate::~startGate() {}

	//初期化
	void startGate::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		/*auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);*/
		//タグをつける
		//AddTag(L"startGate");

		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"TEX_CHEESE");

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);


	}
}
//end basecross
