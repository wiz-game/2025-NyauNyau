
/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

#include "ShadowObject.h"
#include "RaycastLine.h"
namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		// カメラの設定
		auto mainCamera = ObjectFactory::Create<MainCamera>();
		auto phase1Camera = ObjectFactory::Create<Phase1Camera>();
		phase1Camera->SetEye(Vec3(50.0f, 15.0f, 5.0f));
		phase1Camera->SetAt(Vec3(-5.0f, -5.0f, 5.0f));

		// カメラへの参照を保持しておく
		m_mainCamera = mainCamera;
		m_phase1Camera = phase1Camera; 

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		if (currentPhase == GamePhase::Phase1)
			view->SetCamera(m_mainCamera);
		if (currentPhase == GamePhase::Phase2)
			view->SetCamera(m_mainCamera);



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
				Vec3(100.0f, 50.0f, 1.0f),
				Vec3(0.0f, -XM_PI / 2, 0.0f),
				Vec3(-5.0f, 4.0f, 0.0f)
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
			Vec3(50.0f, 10.0f, 100.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(19.0f, -10.5f, 0.0f)
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

		for (auto& v : vec)
		{
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

	void GameStage::CreateShadowFloor()
	{
		vector<vector<Vec3>> vec = {
		{
			Vec3(1.0f, 20.0f, 20.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(-5.0f, -10.5f, -30.0f)
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
		vector<shared_ptr<ShadowFloor>> grounds; // 生成した `Ground` を管理するリスト

		for (auto& v : vec) {
			auto ptrGround = AddGameObject<ShadowFloor>(v[0], v[1], v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"Ground_1" + to_wstring(index);

			ptrGround->AddTag(uniqueTag);  // ユニークなタグを適用
			grounds.push_back(ptrGround);    // `Ground` をリストに保存

			index++; // 次のオブジェクトのためにインデックスを増加
		}

		// すべての `Ground` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < grounds.size(); ++i) {
			wstring uniqueName = L"Ground_1" + to_wstring(i);  // ユニーク名を生成
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
			Vec3(-4.7f,0.005f,-40.0f)
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
				Vec3(3.75f, 3.0f, 3.0f),
				Vec3(0.0f, 0.0f + XMConvertToRadians(270) , 0.0f),
				Vec3(-4.75f, 1.0f, -40.0f)
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
			auto ptrPlayer = AddGameObject<Player>(v[0], v[1], v[2]);
			m_mainCamera->SetTargetObject(ptrPlayer);

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

	void GameStage::CreateEnemy()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(-0.01f,9.0f,9.0f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-4.7f,4.0f,-50.0f)
		}
		};
		for (auto& v : vec) {

			auto ptrEnemy = AddGameObject<Enemy>(v[0], v[1], v[2]);

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
			Vec3(-4.7f,0.005f,30.0f)
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
		vector< vector <Vec3> > vec ={
		{
			Vec3(1.0f,1.0f,0.5f),
			Vec3(0.0f,0.0f + XMConvertToRadians(270),0.0f),
			Vec3(-4.6f,3.0f,-5.0f)

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
		SetSharedGameObject(L"Box", ptrBox);
		//タグをつける
		//ptrBox->AddTag(L"Box");
	}


	//void GameStage::Initialize()
	//{





		// Boxオブジェクトと他のゲームオブジェクトをセットアップ
		//boxObject = std::make_shared<GameObject>();
		//gameObjects.push_back(boxObject);

		// Phase1 では Box 以外を固定
		//for (auto& obj : gameObjects) 
		//{
		//	if (obj != boxObject) {
		//		obj->SetUpdateActive(true);
		//		obj->;
		//	}
		//}


	//}


	//void GameStage::CreateTestShadowBox()
	//{
	//	vector<vector<Vec3>> vec =
	//	{
	//		{
	//			Vec3(0.0f, 0.5f, 0.5f),
	//			Vec3(0.0f, 0.0f, 0.0f),
	//			Vec3(-4.75f, 1.2f, -7.0f)
	//		},

	//	};

		//int index = 0; // ユニーク名用のインデックス
		//vector<shared_ptr<TestShadowBox>> TestShadowBoxs; // 生成した `` を管理するリスト

		//for (auto& v : vec)
		//{
		//	auto ptrTestShadowBox = AddGameObject<TestShadowBox>(v[0], v[1], v[2]);

		//	// ユニーク名を生成
		//	wstring uniqueTag = L"TestShadowBox_" + to_wstring(index);

		//	ptrTestShadowBox->AddTag(uniqueTag);  // ユニークなタグを適用
		//	TestShadowBoxs.push_back(ptrTestShadowBox);    // `` をリストに保存
		//	index++; // 次のオブジェクトのためにインデックスを増加		

		//}

		//// すべての `` を共有ゲームオブジェクトとして登録
		//for (size_t i = 0; i < TestShadowBoxs.size(); i++)
		//{
		//	wstring uniqueName = L"TestShadowBox_" + to_wstring(i);  // ユニーク名を生成
		//	SetSharedGameObject(uniqueName, TestShadowBoxs[i]);      // ユニーク名で共有登録

		//}



	//}


	void GameStage::OnCreate() {
		try {

			LoadTextures();

			//ビューとライトの作成
			CreateViewLight();
			//壁の作成
			CreateWall();
			//ステージの作成
			CreateGround();

			//ステージの見た目(ガチ雑スクリプトのため後で消す)
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 20.0f, 40.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, -10.5f, -30.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 10.0f, 40.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, 10.5f, -30.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 50.0f, 100.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, 35.5f, 0.0f)
			);

			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 20.0f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, -8.5f, -5.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 15.0f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, -8.5f, 5.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 17.0f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, -8.5f, 15.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 20.0f, 20.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, -8.5f, 25.0f)
			);







			//AddGameObject<ShadowFloor>(
			//	Vec3(1.0f, 20.0f, 40.0f),  
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-5.0f, -8.5f, 20.0f)
			//);


			//AddGameObject<ShadowFloor>(
			//	Vec3(1.0f, 20.0f, 10.0f),  // 10,1,10
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-5.0f, -9.5f, -5.0f)
			//);






			//Boxの作成
			CreateBox();

			//CreateTestShadowBox();

			//SpotLightの作成
			auto spotLight = AddGameObject<SpotLight>();
			SetSharedGameObject(L"SpotLight", spotLight);
			//影の作成
			AddGameObject<ShadowObject>();
			//プレイヤーの作成
			CreatePlayer();
			//エネミーの作成
			CreateEnemy();
			//スタートの作成
			CreatestartGate();
			//ゴールの作成
			//CreategoalGate();
			AddGameObject<goalGate>(
				Vec3(0.01f, 2.5f, 1.5f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-4.7f, 2.0f, 25.0f)
			);
			//チーズの作成
			CreateCheese();

			//スプライトオブジェクト
			AddGameObject<Phase1>();


			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Gamebgm", XAUDIO2_LOOP_INFINITE, 0.1f);


			// ゲーム開始時のフェーズ設定
			currentPhase = GamePhase::Phase1;

		}
		catch (...) {
			throw;
		}
	}
	void GameStage::OnUpdate()
	{


		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameStage>());


		auto& app = App::GetApp();

		auto device = app->GetInputDevice();
		auto pad = device.GetControlerVec()[0];

		//スタートボタンを押したときにボーズする
		if (pad.wPressedButtons & XINPUT_GAMEPAD_START)
		{

			auto scene = App::GetApp()->GetScene<Scene>();
			scene->PauseGame();
			m_PauseFlag = !m_PauseFlag;

			if (m_PauseFlag)
			{

				m_Pause = AddGameObject<pauseSprite>();
				m_pauseSprite = true;
			}
			else
			{
				if (m_pauseSprite)
				{
					RemoveGameObject<pauseSprite>(m_Pause);
					m_pauseSprite = false;
				}
				m_PauseFlag = false;
			}
		}

	}

	//タイトルに戻る
	void GameStage::OnPushA()
	{
		if (m_PauseFlag)
		{
			auto scene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");

			//一定時間後にスプライトを削除する（タイトル画面からゲームステージに移るタイミング）
			PostEvent(5.0f, GetThis<ObjectInterface>(), scene, L"RemoveSprite");

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
		app->RegisterTexture(L"TEX_YUKA", texPath + L"floor.png");
		app->RegisterTexture(L"TEX_PAUSE", texPath + L"pauseSprite.png");
		app->RegisterTexture(L"TEX_NEZUMI", texPath + L"nezumi.png");
		app->RegisterTexture(L"TEX_NEZUMI2", texPath + L"nezumi2.png");
		app->RegisterTexture(L"TEX_SHELF", texPath + L"Shelf.png");
		app->RegisterTexture(L"TEX_ENEMY", texPath + L"Cat.png");
		app->RegisterTexture(L"TEX_START", texPath + L"Goal.png");
		app->RegisterTexture(L"TEX_GOAL", texPath + L"Goal.png");
		app->RegisterTexture(L"TEX_BbuttondeGameStart", texPath + L"BbuttondeGameStart.png");



	}

	void GameStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);

	}

	void GameStage::SwitchCamera()
	{
		
	}

	void GameStage::OnUpdate2()
	{


		if (currentPhase == GamePhase::Phase1)
		{	

			auto gameObjectVec = GetGameObjectVec();
			for (auto obj : gameObjectVec)
			{

				/*if (gameObjectVec.empty())
				{
					std::cout << "GetGameObjectVec() によって取得されたオブジェクトのリストが空です。" << std::endl;
					return;
				}*/

				if (obj->FindTag(L"Box")) //dynamic_pointer_cast<Box>(obj) 
				{
					obj->SetUpdateActive(true);
				}
				else
				{
					obj->SetUpdateActive(false);
				}


			}
		}


		// BボタンでPhase2(GameStart)へ
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
		{
			currentPhase = GamePhase::Phase2;



			auto gameObjectVec = GetGameObjectVec();
			for (auto obj : gameObjectVec)
			{
				if (obj->FindTag(L"Box")) //dynamic_pointer_cast<Box>(obj) 
				{
					obj->SetUpdateActive(false);
				}
				else
				{
					obj->SetUpdateActive(true);

				}
			}



		}


	}
}
	

//end basecross
