
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
//#include  "cmath"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------

	enum class GamePhase
	{
		Phase1,  //Box のみ操作可能
 	    Phase2,   //全オブジェクトが動作開始

	};

	enum class GameControlMode 
	{
		SelectBox,  // 現在、操作するBoxを選択している最中であることを示すモード
		ControlBox  // 特定のBoxを選択し、そのBoxを操作している最中であることを示すモード
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

		void CreateShadowBall();

		std::weak_ptr<PauseManager> m_pauseManager;//ポーズマネージャーへの参照
		std::weak_ptr<SettingStage> m_settingStage;//セッティングステージへの参照
		std::vector<std::weak_ptr<GameStageUI>> m_gameStageUI;//UIスプライトへの参照

		//入力ハンドラー
		InputHandler<GameStage> m_InputHandler;

		shared_ptr<SoundItem> m_BGM;

		shared_ptr<SingleView> m_mainView; // メインカメラへの参照
		shared_ptr<SingleView> m_phase1View;

		GamePhase currentPhase = GamePhase::Phase1; // 最初に設定されているPhase

		std::vector<std::shared_ptr<Box>> m_controllableBoxes;
		// SelectBoxモードの時に、ハイライトされているBox
		int m_selectedBoxIndex;

		// 現在のゲームの操作モード（SelectBox か ControlBox か）を保持する
		GameControlMode m_currentControlMode;
		// ControlBoxモードの時に、現在実際に操作対象となっているBoxオブジェクトへのポインタ
		std::shared_ptr<Box> m_currentlyControlledBox;
		
		bool m_stickMovedLeftLastFrame;  // 前のフレームで左に倒されていたか
        bool m_stickMovedRightLastFrame; // 前のフレームで右に倒されていたか

		//std::shared_ptr<Box> boxObject;
		//std::vector<std::shared_ptr<GameObject>> gameObjects;
		float m_Time;
		bool m_isStageFadingOut;
		float m_fadeTimer;
		float m_filterFadeTimer;

		

	public:
		//構築と破棄
		GameStage() :
			Stage(),
			m_Time(0.0f),
			m_isStageFadingOut(false),
			m_fadeTimer(0.0f),
			m_filterFadeTimer(0.0f)
		{}
		virtual ~GameStage() {}


		void OnPushA();	

		// 現在の操作モードを取得する関数
		GameControlMode GetCurrentControlMode() const;
		// 現在ハイライトされているBoxを操作対象に設定し、ControlBoxモードへ移行しようと試みる関数
		void AttemptToControlSelectedBox();
		// 現在操作中のBoxの操作を終了し、SelectBoxモードへ戻る関数
		void ReleaseControlOfBox();

		// SelectBoxモードで、次のBoxを選択候補としてハイライトするための関数
		void SelectNextBox();
		// SelectBoxモードで、前のBoxを選択候補としてハイライトするための関数
		void SelectPreviousBox();


		//初期化		
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		virtual void OnDestroy()override;


	};
}
//end basecross

