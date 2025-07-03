
/*!
@file GameStage2.h
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
#include "Table.h"

#include "GameStagePointerUI.h"
#include "FadeScreen.h"

//#include  "cmath"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------

	enum class GamePhase2
	{
		Phase1,   //Box のみ操作可能なフェーズ
		Phase2,   //全オブジェクトが動作開始するフェーズ

	};

	enum class GameControlMode2
	{
		SelectBox,  // 現在、操作するBoxを選択している最中であることを示すモード
		ControlBox  // 特定のBoxを選択し、そのBoxを操作している最中であることを示すモード
	};

	enum class CameraSelect2
	{
		openingCamera,
		phase1Camera,
	};


	class GameStage2 : public Stage {
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
		//本棚
		void CreateBookShelf();
		//窓
		void CreateMado();
		//テクスチャの読込
		void LoadTextures();
		//モデルの読込
		void LoadModels();

		void CreateBox();
		//void CreateTestShadowBox();

		//プレイヤーの作成
		void CreatePlayer();

		//エネミーの作成
		void CreateEnemy();

		//ギミック（仮）の作成
		void CreateShadowBall();

		//カメラマンの作成
		void CreateCameraman();

		std::weak_ptr<PauseManager> m_pauseManager;//ポーズマネージャーへの参照
		std::weak_ptr<SettingStage> m_settingStage;//セッティングステージへの参照
		std::vector<std::weak_ptr<GameStageUI>> m_gameStageUI;//UIスプライトへの参照

		//入力ハンドラー
		InputHandler<GameStage2> m_InputHandler;

		shared_ptr<SoundItem> m_BGM;

		shared_ptr<SingleView> m_mainView; // メインカメラへの参照
		shared_ptr<SingleView> m_phase1View;
		shared_ptr<SingleView> m_OpeningCameraView;

		GamePhase2 currentPhase = GamePhase2::Phase1; // 最初に設定されているPhase

		// ステージ上に存在する、プレイヤーが操作できるBoxオブジェクトのリスト
		std::vector<std::shared_ptr<Box>> m_controllableBoxes;

		// SelectBoxモードの時に、ハイライトされているBox
		int m_selectedBoxIndex;
		int m_lastNotifiedIndex;//UIに最後に通知したインデックス

		// 現在のゲームの操作モード（SelectBox か ControlBox か）を保持する
		GameControlMode2 m_currentControlMode;

		// ControlBoxモードの時に、現在実際に操作対象となっているBoxオブジェクトへのポインタ
		std::shared_ptr<Box> m_currentlyControlledBox;

		std::weak_ptr<GameStagePointerUI> m_selectionPointerUI;//選択ポインターUIへのポインタ

		bool m_stickMovedLeftLastFrame;  // 前のフレームで左に倒されていたか
		bool m_stickMovedRightLastFrame; // 前のフレームで右に倒されていたか

		float m_Time;
		bool m_isStageFadingOut;
		float m_fadeTimer;
		float m_filterFadeTimer;

		shared_ptr<PNTBoneModelDraw> m_drawModelComp;

		CameraSelect2 m_CameraSelect;

		float m_initialUpdateTimer; // 最初の数秒間を計るためのタイマー
		bool m_isInitialUpdatePeriod; // 最初の数秒間の間かを示すフラグ

		weak_ptr<FadeScreen> m_fadeScreen;
		//ゲームオーバーフラグ
		bool m_isGameOver = false;

	public:
		//構築と破棄
		GameStage2() :
			Stage(),
			m_Time(0.0f),
			m_isStageFadingOut(false),
			m_fadeTimer(0.0f),
			m_filterFadeTimer(0.0f),
			m_lastNotifiedIndex(-2)
		{}
		virtual ~GameStage2() {}


		void OnPushA();

		// 現在の操作モードを取得する関数
		GameControlMode2 GetCurrentControlMode() const;
		// 現在ハイライトされているBoxを操作対象に設定し、ControlBoxモードへ移行しようと試みる関数
		void AttemptToControlSelectedBox();
		// 現在操作中のBoxの操作を終了し、SelectBoxモードへ戻る関数
		void ReleaseControlOfBox();

		// SelectBoxモードで、次のBoxを選択候補としてハイライトするための関数
		void SelectNextBox();
		// SelectBoxモードで、前のBoxを選択候補としてハイライトするための関数
		void SelectPreviousBox();

		std::shared_ptr<Table> GetTableObject() const; // Tableオブジェクトを取得する関数


		CameraSelect2 GetCameraSelect() const
		{
			return m_CameraSelect;
		}

		void ToPhase1Camera();

		//初期化		
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		virtual void OnDestroy()override;

		void UpdateSelectionUI();

		void OnPlayerCollision(shared_ptr<GameObject> player, shared_ptr<GameObject> other);
		void StartGameOver();

	};
}
//end basecross

