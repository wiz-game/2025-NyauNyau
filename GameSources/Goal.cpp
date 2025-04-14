
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
		if (!ptrColl) return; // 衝突判定コンポーネントがない場合は処理を終了

		//auto player = GetStage()->FindObjectByTag(L"Player"); // "Player"タグを持つオブジェクトを取得
		//if (!player) return; // プレイヤーが見つからない場合は処理を終了

		//if (ptrColl->IsColliding(player)) // プレイヤーとgoalGateが衝突したかチェック
		//{
		//	auto playerObj = dynamic_pointer_cast<Player>(player);//Playerオブジェクトとしてキャスト
		//	if (playerObj && playerObj->hasCheese()) // プレイヤーがチーズを持っている場合
		//	{
		//		gameClear(); // ゲームクリア処理を実行
		//	}
		//}
	}
}
//end basecross
