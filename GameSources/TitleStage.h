/*!
@file Character.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"
#include "TitleSprite.h"
#include "SettingStage.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込
		void OnDestroy();

		//入力ハンドラー
		InputHandler<TitleStage> m_InputHandler;
		shared_ptr<SoundItem> m_BGM;
		std::vector<std::shared_ptr<TitleSprite>> m_titleSprite;
		std::weak_ptr<SettingStage> m_settingStage;
		
		const int spriteCount = 11;
		float phaseIncrement = 0.5f;
		float m_totalTime;


	public:
		//構築と破棄
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

		//Aボタン
		void OnPushA();
		void OnPushB(){}
	};
}
//end basecross
