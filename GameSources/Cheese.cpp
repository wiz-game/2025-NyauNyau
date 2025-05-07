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
		m_Position(Position),
		isTarget(false),
		followDistance(0.5f)
	{
	}
	Cheese::~Cheese() {}


	void Cheese::OnCreate()
	{
		//ドローコンポーネントの追加と設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();		
		//ptrDraw->SetRasterizerState(RasterizerState::Wireframe);
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"TEX_CHEESE");
		SetAlphaActive(true);
		

		//トランスフォームコンポーネントの取得と設定
		m_transComp = GetComponent<Transform>();
		m_transComp->SetPosition(m_Position);
		m_transComp->SetRotation(m_Rotation);
		m_transComp->SetScale(m_Scale);
		//タグ
		AddTag(L"Cheese");


	}

	void Cheese::OnUpdate()
	{
		//Playerタグの取得
		auto playerSh = GetStage()->GetSharedGameObject<Player>(L"Player_0");
		Vec3 playerPos = playerSh->GetComponent<Transform>()->GetPosition();
		
		//プレイヤーの進行方向の取得
		Vec3 playerForward = playerSh->GetComponent<Transform>()->GetForward();

		Vec3 cheesePos = m_transComp->GetPosition();
		Vec3 targetPos = playerPos - (playerForward * followDistance);

		//PlayerとCheeseの二点間の距離計算
		auto len = length(playerPos - cheesePos);

		//追尾処理
		if (len < 0.3f) {

			isTarget = true;
		}
		//追尾中ならプレイヤーの後方へ移動
		if (isTarget)
		{
			//プレイヤーの後方に位置を設定
			Vec3 direction = Vec3(targetPos - cheesePos).normalize();
			Vec3 m_Scale(Vec3(0.25f));

			//一定距離を保ちつつ、滑らかに移動
			if (length(targetPos - cheesePos) > 0.1f)
			{
				m_transComp->SetPosition(cheesePos + direction * 0.1);
			}
		}
	}

}
//end basecross
