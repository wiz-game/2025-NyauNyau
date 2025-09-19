
/*!
@file GameStage3.h
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
#include "SpotLight.h"
#include "GameStagePointerUI.h"
#include "FadeScreen.h"

//#include  "cmath"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------

	enum class GamePhase3
	{
		Phase0,
		Phase1,   //Box のみ操作可能なフェーズ
		Phase2,   //全オブジェクトが動作開始するフェーズ

	};

	enum class GameControlMode3
	{
		SelectBox,  // 現在、操作するBoxを選択している最中であることを示すモード
		ControlBox  // 特定のBoxを選択し、そのBoxを操作している最中であることを示すモード
	};

	enum class CameraSelect3
	{
		openingCamera,
		phase1Camera,
	};


	class GameStage3 : public Stage {
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
		//光源の作成
		void CreateSpotLight();

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
		std::weak_ptr<GameStageUI> m_stageUI;//ステージUIスプライトへの参照

		std::weak_ptr<GameStagePointerUI> m_ase;//UIスプライトへの参照

		//入力ハンドラー
		InputHandler<GameStage3> m_InputHandler;

		shared_ptr<SoundItem> m_BGM;

		shared_ptr<SingleView> m_mainView; // メインカメラへの参照
		shared_ptr<SingleView> m_phase1View;
		shared_ptr<SingleView> m_OpeningCameraView;

		GamePhase3 currentPhase = GamePhase3::Phase0; // 最初に設定されているPhase

		// ステージ上に存在する、プレイヤーが操作できるBoxオブジェクトのリスト
		std::vector<std::shared_ptr<Box>> m_controllableBoxes;

		// SelectBoxモードの時に、ハイライトされているBox
		int m_selectedBoxIndex;
		int m_lastNotifiedIndex;//UIに最後に通知したインデックス

		// 現在のゲームの操作モード（SelectBox か ControlBox か）を保持する
		GameControlMode3 m_currentControlMode;

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

		CameraSelect3 m_CameraSelect;

		float m_isTimer; // phase1の時間制限を計るためのタイマー
		bool m_isTimerflag; // タイマーの間かを示すフラグ

		float m_isShortTimer; // 最初の数秒間を計るためのタイマー
		bool m_isShortTimerflag; // 最初の数秒間の間かを示すフラグ

		weak_ptr<FadeScreen> m_fadeScreen;
		//ゲームオーバーフラグ
		bool m_isGameOver = false;

		// タイマー時計用のUIオブジェクト 
		std::weak_ptr<GameStageUI> m_timerClockFrameUI;  // 時計の外枠
		std::weak_ptr<GameStageUI> m_timerClockFaceUI;   // 時計の文字盤（中）
		std::weak_ptr<GameStageUI> m_timerSecHandUI;   // 時計の秒針

		bool isTimerSoundFlag;

		shared_ptr<SoundItem> m_TimerSound;

		//shared_ptr<GameStageUI> m_exclamationMarkUI; // Exclamation markUIへのポインタ  
		//bool m_isExclamationMarkActive; // Exclamation markが表示されているか           

		// Exclamation markの表示制御用に追加  //
		//bool m_isExclamationMark;    // Exclamation markが表示中かを示すフラグ       
		//float m_exclamationMarkTimer;   // Exclamation markの表示時間を計るタイマー  

		bool CntlUIDrawing;//コントローラUIが表示されているかどうか
		bool CntlCheck;//コントロールが接続されているかどうか


	public:
		//構築と破棄
		GameStage3() :
			Stage(),
			m_Time(0.0f),
			m_isStageFadingOut(false),
			m_fadeTimer(0.0f),
			m_filterFadeTimer(0.0f),
			m_lastNotifiedIndex(-2),
			CntlUIDrawing(false),
			CntlCheck(false)
		{}
		virtual ~GameStage3() {}


		void OnPushA();

		// 現在の操作モードを取得する関数
		GameControlMode3 GetCurrentControlMode() const;
		// 現在ハイライトされているBoxを操作対象に設定し、ControlBoxモードへ移行しようと試みる関数
		void AttemptToControlSelectedBox();
		// 現在操作中のBoxの操作を終了し、SelectBoxモードへ戻る関数
		void ReleaseControlOfBox();

		// SelectBoxモードで、次のBoxを選択候補としてハイライトするための関数
		void SelectNextBox();
		// SelectBoxモードで、前のBoxを選択候補としてハイライトするための関数
		void SelectPreviousBox();

		std::shared_ptr<Table> GetTableObject() const; // Tableオブジェクトを取得する関数


		CameraSelect3 GetCameraSelect() const
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

		void CntlUIDraw();
		void NotUIDraw();

		void Reset();

	};
}
//end basecross

