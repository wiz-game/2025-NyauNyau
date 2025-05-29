/*!
@file Character.h
@brief ステージセレクト画面
*/

#pragma once
#include "stdafx.h"
#include "SelectStageSprite.h"
#include "FootprintSprite.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ステージセレクトクラス
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込
		void OnDestroy();
		shared_ptr<SoundItem> m_BGM;

		std::vector<std::weak_ptr<SelectStageSprite>> m_stageSprites;//ステージスプライトを管理する
		std::vector<std::weak_ptr<FootprintSprite>> m_footprints;//足跡の管理
		std::shared_ptr<FootprintSprite> m_transFootprints;

		std::shared_ptr<SelectStageSprite> catPointSprite;

		void ChangeSelect(int num);
		bool m_CntrolLock;
		float m_select;//矢印の位置
		bool footprintsStart;
		//void DrawString();

		//矢印のY軸を変更させる関数
		void SetSelectYPosition(int StageNum);

		//ネコの足跡の処理
		void CreateFootprints();


	public:
		//構築と破棄
		SelectStage() :Stage(),m_CntrolLock(false),footprintsStart(false)
		{
		}
		virtual ~SelectStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

	};
	
}
//end basecross