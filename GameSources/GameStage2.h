/*!
@file GameStage.h
@brief ゲームステージ2
*/

#pragma once
#include "stdafx.h"
#include "PauseSprite.h"
#include "MainCamera.h"
#include "PauseManager.h"
#include "Phase1Camera.h"
#include "SettingStage.h"
#include "GameStageUI.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	enum class GamePhase2
	{
		Phase1,  //Box のみ操作可能
		Phase2,   //全オブジェクトが動作開始

	};

	class GameStage2 : public Stage {

		//ビューの作成
		void CreateViewLight();
		//壁の生成
		void CreateWall();
		//床の生成
		void CreateGround();
		//棚の作成
		void CreateShadowFloor();
		//スタートの作成
		void CreatestartGate();
		//ゴールの作成
		void CreategoalGate();
		//テーブルの作成
		void CreateTable();

		//テクスチャの読込
		void LoadTextures();
		//モデルの読込
		void LoadModels();

		void CreateBox();


		//プレイヤーの生成
		void CreatePlayer();

		//エネミーの生成
		void CreateEnemy();


		shared_ptr<SingleView> m_mainView; // メインカメラへの参照
		shared_ptr<SingleView> m_phase1View;

		std::weak_ptr<PauseManager> m_pauseManager;//ポーズマネージャーへの参照
		std::weak_ptr<SettingStage> m_settingStage;//セッティングステージへの参照
		std::vector<std::weak_ptr<GameStageUI>> m_gameStageUI;//UIスプライトへの参照

		//入力ハンドラー
		InputHandler<GameStage2> m_InputHandler;

		shared_ptr<SoundItem> m_BGM;

		GamePhase2 currentPhase = GamePhase2::Phase1; // 最初に設定されているPhase


	public:
		//構築と破棄
		GameStage2() :Stage() {}
		virtual ~GameStage2() {}

		void OnPushA();


		//初期化		
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		virtual void OnDestroy()override;

	};
}
//end basecross
