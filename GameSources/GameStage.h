
/*!
@file GameStage.h
@brief ゲームステージ
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

	enum class GamePhase
	{
		Phase1,  //Box のみ操作可能
 	    Phase2,   //全オブジェクトが動作開始

	};
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
		//棚の作成
		void CreateShadowFloor();
		//テーブルの作成
		void CreateTable();
		//テクスチャの読込
		void LoadTextures();
		//モデルの読込
		void LoadModels();


		void CreateBox();
		//void CreateTestShadowBox();

		//プレイヤーの生成
		void CreatePlayer();

		//エネミーの生成
		void CreateEnemy();


		std::weak_ptr<PauseManager> m_pauseManager;//ポーズマネージャーへの参照
		std::weak_ptr<SettingStage> m_settingStage;//セッティングステージへの参照
		std::vector<std::weak_ptr<GameStageUI>> m_gameStageUI;//UIスプライトへの参照

		//入力ハンドラー
		InputHandler<GameStage> m_InputHandler;


		shared_ptr<SoundItem> m_BGM;

		shared_ptr<SingleView> m_mainView; // メインカメラへの参照
		shared_ptr<SingleView> m_phase1View;

		GamePhase currentPhase = GamePhase::Phase1; // 最初に設定されているPhase


		//std::shared_ptr<Box> boxObject;
		//std::vector<std::shared_ptr<GameObject>> gameObjects;

		

	public:
		//構築と破棄
		GameStage() :Stage(){}
		virtual ~GameStage() {}
		void OnPushA();	

		//初期化		
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		virtual void OnDestroy()override;

		//void Initialize();

	};
}
//end basecross

