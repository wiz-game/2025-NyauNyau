
/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "PauseSprite.h"
#include "MainCamera.h"
#include "Phase1Camera.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------

	enum class GamePhase
	{
		Phase1,  //Box のみ操作可能
 	    Phase2   //全オブジェクトが動作開始

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
		InputHandler<GameStage> m_InputHandler;


		shared_ptr<SoundItem> m_BGM;

		shared_ptr<SingleView> m_mainView; // メインカメラへの参照
		shared_ptr<SingleView> m_phase1View;

		GamePhase currentPhase = GamePhase::Phase1;


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

