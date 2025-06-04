/*!
@file Character.h
@brief ゲームオーバーステージ
*/

#pragma once
#include "stdafx.h"
#include "TitleSprite.h"

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
		//std::vector<std::shared_ptr<GameOverSprite>> m_GameOverSprite;

	public:
		//構築と破棄
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

		//Aボタン
		void OnPushA();

	};
}
//end basecross
