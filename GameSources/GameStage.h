
/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "PauseSprite.h"
#include "MainCamera.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();
		//壁の生成
		void CreateWall();
		//床の生成
		void CreateGround();
		//スタートの作成
		void CreatestartGate();
		//ゴールの作成
		void CreategoalGate();
		//チーズの作成
		void CreateCheese();
		//テクスチャの読込
		void LoadTextures();

		void CreateBox();
		
		//プレイヤーの生成
		void CreatePlayer();

		//ポーズフラグ
		bool m_PauseFlag = false;
		bool m_pauseSprite = false;
		int m_SpriteNum;//今選択しているスプライト


		void ChangeSelect(int num);
		//矢印のY軸を変更させる関数
		void SetSelectPosition(int SpriteNum);
		bool m_CntrolLock;
		float m_selectY;//矢印のY座標の位置
		float m_selectX;//矢印のX座標の位置

		std::vector<std::weak_ptr<pauseSprite>> m_pauseSprites;//ポーズスプライトの変数
		std::shared_ptr<pauseSprite> leftPointSprite;//左矢印
		std::shared_ptr<pauseSprite> Pause;


		//入力ハンドラー
		//InputHandler<GameStage> m_InputHandler;


		shared_ptr<SoundItem> m_BGM;

		shared_ptr<MainCamera> m_mainCamera; // メインカメラへの参照


	public:
		//構築と破棄
		GameStage() :Stage(){}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnPushA();
		virtual void OnDestroy()override;

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

