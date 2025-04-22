
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
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_gameClear(std::make_shared<bool>(false))//クリアしたかどうか（初期値:false）
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
		ptrColl->SetFixed(true);
		//タグをつける
		AddTag(L"Goal");

		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);


	}

	void goalGate::OnUpdate()
	{
		auto ptrColl = GetComponent<CollisionObb>();
		ptrColl->SetFixed(true);//位置固定

		if (!ptrColl) return; // 衝突判定コンポーネントがない場合は処理を終了

		auto playerSh = GetStage()->GetSharedGameObject<Player>(L"Player"); // "Player"タグを取得
		//Vec3 playerPos = playerSh->GetComponent<Transform>()->GetPosition();//Playerの位置

		if (!ptrColl->IsExcludeCollisionObject(playerSh))//衝突判定
		{
			//if (playerSh && playerSh->hasCheese()) // プレイヤーがチーズを持っている場合
			//{
				m_gameClear = true; // ゲームクリア
			//}
		}
	}
}
//end basecross
