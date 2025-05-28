
/*!
@file Character.cpp
@brief ゴールの実体
*/

#include "stdafx.h"
#include "Project.h"
namespace basecross
{
	//構築と破壊
	goalGate::goalGate(const shared_ptr<Stage>& StagePtr,
		Vec3& Scale,
		Vec3& Rotation,
		Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	goalGate::~goalGate() {}

	//初期化
	void goalGate::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(false);
		//タグをつける
		AddTag(L"Goal");

		////影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		////影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"TEX_SHELF");

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);


	}

	void goalGate::OnUpdate()
	{

	}

	void goalGate::OnCollisionEnter(shared_ptr<GameObject>& collision)
	{
		if (dynamic_pointer_cast <Player>(collision))
		{
			auto& app = App::GetApp();
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGoalStage");

		}
	}

}
//end basecross
