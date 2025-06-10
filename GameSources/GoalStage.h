/*!
@file Character.h
@brief ゴールタイトルステージ
*/

#pragma once
#include "stdafx.h"
#include "CatwalkSprite.h"
#include "GameSprite.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゴールステージクラス
	//--------------------------------------------------------------------------------------
	class goalStage : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込


		//入力ハンドラー
		InputHandler<goalStage> m_InputHandler;
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		std::weak_ptr<CatWalkSprite> m_catSprite;
		std::weak_ptr<GameSprite> m_loading;
		std::weak_ptr<GameSprite> m_rat;


		std::vector<std::shared_ptr<GameObject>> m_sprites;



	public:
		//構築と破棄
		goalStage() :Stage() {}
		virtual ~goalStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

		//Aボタン
		void OnPushA();
		void OnPushB(){}
		void OnDestroy();
		void StartCatWalkAnimation();

	};
}
//end basecross
