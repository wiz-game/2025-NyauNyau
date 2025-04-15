/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//構築と破壊
	Cheese::Cheese(const shared_ptr<Stage>& StagePtr
		//const Vec3& Scale,
		//const Vec3& Rotation,
		//const Vec3& Position
	) :
		GameObject(StagePtr),
		//m_Scale(Scale),
		//m_Rotation(Rotation),
		//m_Position(Position),
		direction(2.0f)
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
		m_transComp->SetPosition(Vec3(-4.3f, 0.5f, 2.0f));
		m_transComp->SetScale(Vec3(0.25f));
		//タグ
		AddTag(L"Cheese");


	}

	void Cheese::OnUpdate()
	{
	}

	//Playerタグの取得
	void Cheese::GetTag(shared_ptr<GameObject>& Player)
	{
		if (Player)
		{
			//PlayerとCheeseの二点間の距離計算
			Vec3 playerPos = Player->GetComponent<Transform>()->GetPosition();
			Vec3 cheesePos = m_transComp->GetPosition();
			Vec3 distance = playerPos - cheesePos;

			if (distance.length() < 1.0f) {
				
				Vec3 distance = Vec3(playerPos - cheesePos).normalize();
				m_transComp->SetPosition(cheesePos + direction * 0.05f);
			}

		}

	}


}
//end basecross
