
/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(10.0f, 10.0f, -15.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateWall()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(10.0f,10.0f,1.0f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(0.0f,4.0f,5.0f)
		},
		{
			Vec3(15.0f,10.0f,1.0f),
			Vec3(0.0f,XM_PI / 2,0.0f),
			Vec3(-5.3f,4.0f,2.0f)
		},
		};
		//オブジェクトの作成
		for (auto v : vec)
		{
			AddGameObject<Wall>(v[0], v[1], v[2]);
		}

		auto ptrWall = AddGameObject<Wall>(Vec3(1, 1, 1), Vec3(0, 0, 0), Vec3(1, 0, 0));
		SetSharedGameObject(L"Wall", ptrWall);
		ptrWall->AddTag(L"Wall");

	}

	//スタート
	void GameStage::CreatestartGate()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.7f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-3.0f,0.005f,4.6f)
		}
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<startGate>(v[0], v[1], v[2]);
		}
	}
	void GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>();
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");

	}

	//ゴール
	void GameStage::CreategoalGate()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.7f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(3.0f,0.005f,4.6f)
		}
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<startGate>(v[0], v[1], v[2]);
		}
	}

	//チーズ
	void GameStage::CreateCheese()
	{
	//	vector< vector <Vec3> > vec = {
	//	{
	//		Vec3(0.25),
	//		Vec3(0.0f,0.0f,0.0f),
	//		Vec3(-4.3f,0.001f,2.0f)
	//	}
	//	};
	//	//オブジェクトの作成
	//	for (auto v : vec) {
	//		AddGameObject<startGate>(v[0], v[1], v[2]);
	//	}
	}




	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//壁の作成
			CreateWall();
			//ステージの作成
			AddGameObject<Ground>();
			//Boxの作成
			AddGameObject<Box>();
			//SpotLightの作成
			//AddGameObject<SpotLight>();
			//プレイヤーの作成
			AddGameObject<Player>();
			//スタートの作成
			CreatestartGate();
			//ゴールの作成
			CreategoalGate();
			//チーズの作成
			CreateCheese();




			CreatePlayer();
		}
		catch (...) {
			throw;
		}


	}

	//// テクスチャの読込
	//void GameStage::LoadTextures()
	//{
	//	// アプリケーションオブジェクトを取得する
	//	auto& app = App::GetApp(); // アプリケーションオブジェクト(シングルトン)のインスタンスを取得する

	//	// メディアフォルダの取得
	//	auto mediaPath = app->GetDataDirWString();

	//	// テクスチャフォルダの定義
	//	auto texPath = mediaPath + L"Textures\\";

	//	// テクスチャの読込と登録
	//	app->RegisterTexture(L"TEX_BOX", texPath + L"brick.jpg");
	//}

}
//end basecross
