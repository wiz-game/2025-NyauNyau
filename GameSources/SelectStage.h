/*!
@file Character.h
@brief ステージセレクト画面
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ステージセレクトクラス
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込
		//void OnDestroy();
		//shared_ptr<SoundItem> m_BGM;

		std::vector<std::shared_ptr<SelectStageSprite>> m_stageSprites;

		void ChangeSelect(int um);
		//void DrawString();


	public:
		//構築と破棄
		SelectStage() :Stage() {}
		virtual ~SelectStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新


		bool m_CntrolLock;


	};
	
}
//end basecross
