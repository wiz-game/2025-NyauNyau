/*!
@file Character.h
@brief ステージセレクト画面
*/

#pragma once
#include "stdafx.h"
#include "SelectStageSprite.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ステージセレクトクラス
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込
		//void OnDestroy();
		//shared_ptr<SoundItem> m_BGM;

		std::vector<std::weak_ptr<SelectStageSprite>> m_stageSprites;

		void ChangeSelect(int um);
		bool m_CntrolLock;
		//void DrawString();


	public:
		//構築と破棄
		SelectStage() :Stage(),m_CntrolLock(false)
		{
		}
		virtual ~SelectStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新
	};
	
}
//end basecross
