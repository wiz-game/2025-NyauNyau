/*!
@file Character.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"
#include "Project.h"
#pragma once


namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class StageSelect : public Stage {
		void CreateViewLight(); //ビューの作成
		//void LoadTextures();//テクスチャの読込
		//void OnDestroy();

		//入力ハンドラー
		InputHandler<StageSelect> m_InputHandler;
		//shared_ptr<SoundItem> m_BGM;



	public:
		//構築と破棄
		StageSelect() :Stage() {}
		virtual ~StageSelect() {}

		virtual void OnCreate()override; //初期化
		virtual void OnUpdate()override; //更新

		//Aボタン
		void OnPushA();


	};
	
	class SelectMassege :public StageSelect
	{
		//どのシーンを実行するかを管理
		enum class Scene
		{
			Start,//スタート画面
			Init,//ゲームの初期化
			Game,//ゲームシーン
			End//アプリケーションの終了
		};

		Scene currentScene;

	public:
		static int stageSelect;
		static const int stageMax = 3;

		static bool isPushEnter;
		static bool isPushDwon;
		static bool isPushUp;

		SelectMassege();

		void OnCreate();
		void OnUpdate();
		void drawScene();
		void isRunning();

	};
}
//end basecross
