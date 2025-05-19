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
		std::shared_ptr<SelectStageSprite> leftPointSprite;

		void ChangeSelect(int num);
		bool m_CntrolLock;
		float m_select;//矢印の位置
		//void DrawString();

		//矢印のY軸を変更させる関数
		void SetSelectYPosition(int StageNum);


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