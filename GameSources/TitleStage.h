/*!
@file Character.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"

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


	public:
		//構築と破棄
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

		//Aボタン
		void OnPushA();

	};
}
//end basecross
