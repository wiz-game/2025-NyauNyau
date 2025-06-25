/*!
@file Character.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"
#include "OpelationSprite.h"
#include "SettingStage.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class Opelation : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込
		void OnDestroy();

		//入力ハンドラー
		InputHandler<Opelation> m_InputHandler;
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		std::vector<std::shared_ptr<OpelationSprite>> m_opelationSprite;
		std::weak_ptr<SettingStage> m_settingStage;

		const int spriteCount = 11;
		float phaseIncrement = 0.5f;
		float m_totalTime;
		bool m_once; //一度だけ判定する

	public:
		//構築と破棄
		Opelation() :Stage() {}
		virtual ~Opelation() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

		//Aボタン
		void OnPushA();
		void OnPushB() {}
	};
}
//end basecross
