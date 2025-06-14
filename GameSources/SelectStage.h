/*!
@file Character.h
@brief ステージセレクト画面
*/

#pragma once
#include "stdafx.h"
#include "SelectStageSprite.h"
#include "FootprintSprite.h"
#include "CatwalkSprite.h"
#include "GameSprite.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ステージセレクトクラス
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込
		void OnDestroy();
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		std::vector<std::weak_ptr<SelectStageSprite>> m_stageSprites;//ステージスプライトを管理する
		std::vector<std::weak_ptr<FootprintSprite>> m_footprints;//足跡の管理
		std::shared_ptr<FootprintSprite> m_transFootprints;
		std::shared_ptr<SelectStageSprite> catPointSprite;

		std::weak_ptr<CatWalkSprite> m_catWalk;
		std::weak_ptr<GameSprite> m_loading;
		std::weak_ptr<GameSprite> m_rat;


		int m_catNum;
		bool m_OnPush;


		void ChangeSelect(int num);
		bool m_CntrolLock;
		float m_select;//矢印の位置
		bool footprintsStart;

		//矢印のY軸を変更させる関数
		void SetSelectYPosition(int StageNum);

		//ネコの足跡の処理
		void CreateFootprints();


	public:
		//構築と破棄
		SelectStage() :
			Stage(),
			m_CntrolLock(false),
			footprintsStart(false),
			m_catNum(0)
		{
		}
		virtual ~SelectStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新
		virtual void StartCatWalkAnimation();

	};
	
}
//end basecross