/*!
@file Character.h
@brief ステージセレクト画面
*/

#pragma once
#include "stdafx.h"
#include "SoundSprite.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ステージセレクトクラス
	//--------------------------------------------------------------------------------------
	class SettingStage : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込
		void OnDestroy();

		std::shared_ptr<SoundItem> m_BGM;

		std::vector<std::weak_ptr<SoundSprite>> m_soundSprites;//サウンドスプライトを管理する

		std::shared_ptr<SoundSprite> catPointSprite;
		std::shared_ptr<SoundSprite> Setting;

		float m_volume = 0.01f;//BGMの初期音量(0.0~1.0)
		int m_volumeLevel = 100;

	public:
		//構築と破棄
		SettingStage() :Stage()
		{
		}
		virtual ~SettingStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

		//struct GetBGM {
		//	return m_BGM;
		//};

		//float GetBGM() const
		//{
		//	return m_volume;
		//}

	};

}
//end basecross