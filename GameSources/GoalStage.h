/*!
@file Character.h
@brief ゴールタイトルステージ
*/

#pragma once
#include "stdafx.h"

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


	public:
		//構築と破棄
		goalStage() :Stage() {}
		virtual ~goalStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

		//Aボタン
		void OnPushA();
		void OnDestroy();

	};
}
//end basecross
