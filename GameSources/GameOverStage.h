/*!
@file Character.h
@brief ゲームオーバーステージ
*/

#pragma once
#include "stdafx.h"
#include "TitleSprite.h"
#include "CatwalkSprite.h"
#include "GameSprite.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームスオーバーテージクラス
	//--------------------------------------------------------------------------------------
	class GameOverStage : public Stage {
		void CreateViewLight(); //ビューの作成
		void LoadTextures();//テクスチャの読込
		void OnDestroy();

		//入力ハンドラー
		InputHandler<GameOverStage> m_InputHandler;
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		std::weak_ptr<CatWalkSprite> m_catSprite;
		std::weak_ptr<GameSprite> m_loading;
		std::weak_ptr<GameSprite> m_rat;


		std::vector<std::shared_ptr<GameObject>> m_sprites;
		std::vector<std::shared_ptr<BackTitleButton>> m_SelectSprites;
		std::shared_ptr<SelectStageSprite> catPointSprite;

		int m_SpriteNum;//今選択しているスプライト

		bool m_CntrolLock;
		float m_selectY;//矢印のY座標の位置
		float m_selectX;//矢印のX座標の位置


	public:
		//構築と破棄
		GameOverStage() :
			Stage(),
			m_CntrolLock(false),
			m_SpriteNum(0),
			m_selectX(0.0f),
			m_selectY(0.0f)

		{
		}
		virtual ~GameOverStage() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

		//Aボタン
		void OnPushA();
		void StartCatWalkAnimation();

		void ChangeSelect(int num);
		//矢印のY軸を変更させる関数
		void SetSelectPosition(int SpriteNum);


		//スプライトナンバーのアクセサ
		int GetSpriteNum() const
		{
			return m_SpriteNum;
		}

		void SetSpriteNum(int i)
		{
			m_SpriteNum = i;
		}

	};
}
//end basecross
