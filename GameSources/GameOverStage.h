/*!
@file Character.h
@brief ゲームオーバーステージ
*/

#pragma once
#include "stdafx.h"
#include "TitleSprite.h"
#include "CatwalkSprite.h"
#include "GameSprite.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームスオーバーテージクラス
	//--------------------------------------------------------------------------------------
	class GameOverStage : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込
		void OnDestroy();

		//入力ハンドラー
		InputHandler<GameOverStage> m_InputHandler;
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		std::weak_ptr<CatWalkSprite> m_catSprite;
		std::weak_ptr<GameSprite> m_loading;
		std::weak_ptr<GameSprite> m_rat;


		std::vector<std::shared_ptr<GameObject>> m_sprites;

	public:
		//構築と破棄
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

		//Aボタン
		void OnPushA();
		void StartCatWalkAnimation();
	};
}
//end basecross
