/*!
@file Character.h
@brief ステージセレクト画面
*/

#pragma once
#include "stdafx.h"
#include "SoundSprite.h"
#include "GameStageUI.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ステージセレクトクラス
	//--------------------------------------------------------------------------------------
	class SettingStage : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込
		void OnDestroy();

		std::shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		std::vector<std::weak_ptr<SoundSprite>> m_BGMsoundSprites;//サウンドスプライトを管理する
		std::vector<std::weak_ptr<SoundSprite>> m_SEsoundSprites;//サウンドスプライトを管理する

		std::shared_ptr<SoundSprite> catPointSprite;
		std::shared_ptr<SoundSprite> Setting;
		bool volumeChanged = false;
		bool isBGMSelected = true;
		bool m_MenuNavigationLock = true;

		std::weak_ptr<GameStageUI> m_StageUI;


	public:
		//構築と破棄
		SettingStage() :Stage()
		{
		}
		virtual ~SettingStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新


	};

}
//end basecross