
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
		// カメラの設定
		auto camera = ObjectFactory::Create<MainCamera>();
		camera->SetEye(Vec3(0.0f, 5.0f, -5.5f));
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_mainCamera = camera; // カメラへの参照を保持しておく

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定



		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateWall()
	{
		vector<vector<Vec3>> vec = {
			//{
			//	Vec3(30.0f, 10.0f, 1.0f), 
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, 4.0f, 5.0f)
			//},
			{
				Vec3(30.0f, 10.0f, 1.0f),
				Vec3(0.0f, XM_PI / 2, 0.0f),
				Vec3(-5.3f, 4.0f, 0.0f)
			},

		};

		int index = 0; // ユニーク名用のインデックス
		vector<shared_ptr<Wall>> walls; // 生成した `Wall` を管理するリスト

		for (auto& v : vec) {
			auto ptrWall = AddGameObject<Wall>(v[0], v[1], v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"Wall_" + to_wstring(index);

			ptrWall->AddTag(uniqueTag);  // ユニークなタグを適用
			walls.push_back(ptrWall);    // `Wall` をリストに保存

			index++; // 次のオブジェクトのためにインデックスを増加
		}

		// すべての `Wall` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < walls.size(); ++i) {
			wstring uniqueName = L"Wall_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, walls[i]);      // ユニーク名で共有登録
		}
	}

	void GameStage::CreateGround()
	{
		vector<vector<Vec3>> vec = {
		{
			Vec3(20.0f, 1.0f, 80.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
		},
		//{
		//	Vec3(20.0f, 1.0f, 8.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(-8.0f, -1.0f, 6.0f)
		//},
		//{
		//	Vec3(8.0f, 1.0f, 20.0f),
		//	Vec3(0.0f,  0.0f, 0.0f),
		//	Vec3(0.0f, -1.0f, 6.0f)

		//}

		};

		int index = 0; // ユニーク名用のインデックス
		vector<shared_ptr<Ground>> grounds; // 生成した `Ground` を管理するリスト

		for (auto& v : vec) {
			auto ptrGround = AddGameObject<Ground>(v[0], v[1], v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"Ground_" + to_wstring(index);

			ptrGround->AddTag(uniqueTag);  // ユニークなタグを適用
			grounds.push_back(ptrGround);    // `Ground` をリストに保存

			index++; // 次のオブジェクトのためにインデックスを増加
		}

		// すべての `Ground` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < grounds.size(); ++i) {
			wstring uniqueName = L"Ground_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, grounds[i]);      // ユニーク名で共有登録
		}

	}

	//スタート
	void GameStage::CreatestartGate()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.0f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-4.7f,0.005f,-12.0f)
		}
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<startGate>(v[0], v[1], v[2]);
		}
	}

	//プレイヤー
	void GameStage::CreatePlayer()
	{
		vector<vector<Vec3>> vec =
		{
			{
				Vec3(2.5f, 2.0f, 2.0f),
				Vec3(0.0f, 0.0f + XMConvertToRadians(270) , 0.0f),
				Vec3(-4.75f, 0.50f, -9.0f)
			},
			//{
			//	Vec3(0.0f, 0.25f, 0.25f),
			//	Vec3(0.0f, 90.0f, 0.0f),
			//	Vec3(-8.0f, 0.0f ,4.0f)
			//}

		};

		int index = 0; // ユニーク名用のインデックス
		vector<shared_ptr<Player>> players; // 生成した `Player` を管理するリスト

		for (auto& v : vec) 
		{
			auto ptrPlayer = AddGameObject<Player>(v[0],v[1],v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"Player_" + to_wstring(index);
			
			ptrPlayer->AddTag(uniqueTag);  // ユニークなタグを適用
			players.push_back(ptrPlayer);    // `Player` をリストに保存
			index++; // 次のオブジェクトのためにインデックスを増加		

		}

		players[0]->SetPlayerMove(false);
		//players[1]->SetPlayerMove(true);


		// すべての `Player` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < players.size(); i++) 
		{
			wstring uniqueName = L"Player_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, players[i]);      // ユニーク名で共有登録

		}


	}

	//ゴール
	void GameStage::CreategoalGate()
	{

		//auto ptrgoalGate = AddGameObject<goalGate>(& scale,& rotation,& position);
		//SetSharedGameObject(L"Goal", ptrgoalGate);
		//ptrgoalGate->AddTag(L"Goal");

		vector< vector <Vec3> > vec = {
		{
			Vec3(0.0f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-4.7f,0.005f,15.0f)
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
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.5f,0.5f,0.5f),
			Vec3(0.0f,0.0f + XMConvertToRadians(270),0.0f),
			Vec3(-4.72f,0.80f,2.0f)
		}
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<Cheese>(v[0], v[1], v[2]);
		}
	}

	void GameStage::CreateBox()
	{

		auto ptrBox = AddGameObject<Box>();
		//タグをつける
		ptrBox->AddTag(L"Box");
	}


	void GameStage::OnCreate() {
		try {	

			LoadTextures();

			//ビューとライトの作成
			CreateViewLight();
			//壁の作成
			CreateWall();
			//ステージの作成
			CreateGround();
			//Boxの作成
			CreateBox();
			//SpotLightの作成
			//AddGameObject<SpotLight>();
			//プレイヤーの作成
			CreatePlayer();
			//スタートの作成
			CreatestartGate();
			//ゴールの作成
			//CreategoalGate();
			AddGameObject<goalGate>(
				Vec3(0.0f, 0.7f, 0.5f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-4.7f, 0.005f, 4.0f)
			);
			//チーズの作成
			CreateCheese();

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Gamebgm", XAUDIO2_LOOP_INFINITE, 0.1f);


		}
		catch (...) {
			throw;
		}


	}


	//// テクスチャの読込
	void GameStage::LoadTextures()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp(); // アプリケーションオブジェクト(シングルトン)のインスタンスを取得する

		// メディアフォルダの取得
		auto mediaPath = app->GetDataDirWString();

	    // テクスチャフォルダの定義
		auto texPath = mediaPath + L"Textures\\";

		// サウンドフォルダの定義
		auto soundPath = mediaPath + L"Sounds\\";

		// テクスチャの読込と登録
		//app->RegisterTexture(L"TEX_BOX", texPath + L"brick.jpg");
		app->RegisterTexture(L"TEX_CHEESE", texPath + L"cheese.png");
		app->RegisterTexture(L"TEX_KABE", texPath + L"kabe.jpg");
		app->RegisterTexture(L"TEX_YUKA", texPath + L"yuka.jpg");
		app->RegisterTexture(L"TEX_NEZUMI", texPath + L"nezumi.png");
		app->RegisterTexture(L"TEX_NEZUMI2", texPath + L"nezumi2.png");



	}

	void GameStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}


}
//end basecross
