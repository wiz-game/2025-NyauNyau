
/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

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
		void LoadTextures();

		
		//プレイヤーの生成
		void CreatePlayer();

	public:
		//構築と破棄
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
	};



}
//end basecross

