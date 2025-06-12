
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

		m_mainView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrmainCamera = ObjectFactory::Create<MainCamera>();
		ptrmainCamera->SetEye(Vec3(12.0f, 0.0f, 10.0f));
		ptrmainCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_mainView->SetCamera(ptrmainCamera);


		m_phase1View = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrphase1Camera = ObjectFactory::Create<Phase1Camera>();
		ptrphase1Camera->SetEye(Vec3(10.0f, 30.0f, -60.0f));
		ptrphase1Camera->SetAt(Vec3(10.0f, 20.0f, 0.0f));
		m_phase1View->SetCamera(ptrphase1Camera);

		SetView(m_phase1View);





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
			{
				Vec3(200.0f, 200.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 4.0f, 0.0f)
			},
			//{
			//	Vec3(100.0f, 50.0f, 1.0f),
			//	Vec3(0.0f, -XM_PI / 2, 0.0f),
			//	Vec3(-5.0f, 4.0f, 0.0f)
			//},

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
			Vec3(200.0f, 10.0f, 200.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -10.5f, 0.0f)
		},
			//{
			//	Vec3(20.0f, 1.0f, 8.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-8.0f, -1.0f, 6.0f)
			//},
			//{
			/*	Vec3(8.0f, 1.0f, 20.0f),
				Vec3(0.0f,  0.0f, 0.0f),
				Vec3(0.0f, -1.0f, 6.0f)*/

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
			Vec3(20.0f, 20.0f, 1.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 4.0f, 0.0f)
		},
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

	void GameStage::CreateTable()
	{
		vector<vector<Vec3>> vec = {
		{
		Vec3(30.0f, 30.0f, 30.0f),  // 10,1,10
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(10.0f, 0.0f, -30.0f)
		},
		};

	}


	//スタート
	void GameStage::CreatestartGate()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.0f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-40.0f,0.005f,-0.5f)
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
				Vec3(1.25f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-25.0f, 22.5f, -0.5f)
				//Vec3(-25.0f, 0.5f, -0.2f)
			},

		};

		int index = 0; // ユニーク名用のインデックス
		vector<shared_ptr<Player>> players; // 生成した `Player` を管理するリスト

		for (auto& v : vec)
		{
			auto ptrPlayer = AddGameObject<Player>(v[0], v[1], v[2]);
			auto ptrmainCamera = dynamic_pointer_cast<MainCamera>(m_mainView->GetCamera());
			ptrmainCamera->SetTargetObject(ptrPlayer);

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
			Vec3(9.0f,9.0f,-0.001f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-35.0f,26.25f,-0.5f)
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
		vector< vector <Vec3> > vec = {
		{
			Vec3(1.0f,1.0f,0.5f),
			Vec3(0.0f,0.0f + XMConvertToRadians(270),0.0f),
			Vec3(-40.0f,0.80f,-0.5f)

		}
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<Cheese>(v[0], v[1], v[2]);
		}
	}


	void GameStage::CreateBox()
	{
		vector<vector<Vec3>> vec = {
		{
			Vec3(2.5f, 2.5f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f ,-4.75f, -4.0f)
		},
			//{
			//	Vec3(2.5f, 2.5f, 2.5f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, -4.75f, -7.0f)
			//}


		};

		int index = 0; // ユニーク名用のインデックス
		vector<shared_ptr<Box>> box; // 生成した `Box` を管理するリスト

		for (auto& v : vec) {
			auto ptrBox = AddGameObject<Box>(v[0], v[1], v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"Box_" + to_wstring(index);

			ptrBox->AddTag(uniqueTag);  // ユニークなタグを適用
			box.push_back(ptrBox);    // `Box` をリストに保存

			index++; // 次のオブジェクトのためにインデックスを増加
		}

		// すべての `Box` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < box.size(); ++i) {
			wstring uniqueName = L"Box_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, box[i]);      // ユニーク名で共有登録
		}

		//auto ptrBox = AddGameObject<Box>();
		//SetSharedGameObject(L"Box", ptrBox);

	}



	void GameStage::OnCreate() {
		try {

			LoadTextures();
			LoadModels();

			//ビューとライトの作成
			CreateViewLight();
			//壁の作成
			CreateWall();
			//ステージの作成
			CreateGround();

			AddGameObject<ShadowFloor>(
				Vec3(100.0f, 50.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-65.0f, -3.0f, 0.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(100.0f, 50.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(85.0f, -3.0f, 0.0f)
			);


			AddGameObject<Table>(
				Vec3(3.0f, 6.0f, 1.0f),
				Vec3(0.0f, XM_PIDIV2, 0.0f),
				Vec3(10.0f, -6.0f, -25.0f)
			);


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
				Vec3(1.5f, 1.5f, 0.001f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(45.0f, 22.75f, -0.1f)
			);
			//チーズの作成
			CreateCheese();

			//スプライトオブジェクト
			AddGameObject<Phase1>();

			auto UI = AddGameObject<GameStageUI>();
			UI->SetTexture(L"TEX_GameStageUI");
			UI->SetPosition(0, 290.0f, 0);
			UI->SetScale(1.5f, 1.0f, 1.0f);
			m_gameStageUI.push_back(UI);


			auto buttonUI = AddGameObject<GameStageUI>();
			buttonUI->SetTexture(L"TEX_GameButtonUI");
			buttonUI->SetPosition(520.0f, -320.0f, 0);
			buttonUI->SetScale(0.5f, 0.6f, 1.0f);
			m_gameStageUI.push_back(buttonUI);

			auto stage = AddGameObject<GameStageUI>();
			stage->SetTexture(L"TEX_STAGE1");
			stage->SetPosition(0, 0, 0);
			stage->SetScale(2.0f, 2.0f, 1.0f);
			stage->SetColor(1.0f, 1.0f, 1.0f, 0.5f);
			m_gameStageUI.push_back(stage);


			auto scene = App::GetApp()->GetScene<Scene>();
			auto volume = scene->m_volumeBGM;

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Gamebgm", XAUDIO2_LOOP_INFINITE, volume);

			m_pauseManager = AddGameObject<PauseManager>();
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
		auto delta = app->GetElapsedTime();

		auto scene = app->GetScene<Scene>();
		wstring log = scene->GetDebugString();
		wstringstream wss(log);


		m_Time += delta;

		if (m_Time > 0.3f && !m_isStageFadingOut)
		{
			m_isStageFadingOut = true;
		}

		if (m_isStageFadingOut)
		{
			//スプライトが有効で、まだ表示されていたら
			auto stageSpr = m_gameStageUI[2].lock();
			if (stageSpr && stageSpr->IsDrawActive())
			{
				//アニメーションにかける時間
				const float fadeOutDuration = 0.5f;
				m_fadeTimer += delta;

				if (m_fadeTimer < fadeOutDuration)
				{
					//アニメーションの進歩率(0.0から1,0)を計算
					float progress = m_fadeTimer / fadeOutDuration;
					if (progress > 1.0f)//progressが1.0を超えないように
					{
						progress = 1.0f;
					}

					float startScaleX = 2.0f;
					float endScaleX = 2.2f;
					float startScaleY = 2.0f;
					float endScaleY = 2.2f;

					float easedProgress = 1.0f - pow(1.0f - progress, 2.0f); // 2乗は緩やかなカーブ

					float currentScaleX = startScaleX + (endScaleX - startScaleX) * easedProgress;
					float currentScaleY = startScaleY + (endScaleY - startScaleY) * easedProgress;

					stageSpr->SetScale(currentScaleX, currentScaleY, 1.0f);

					float currentAlpha = 1.0f - progress;
					stageSpr->SetColor(1.0f, 1.0f, 1.0f, currentAlpha);


					wss << L"Delta: " << delta << L"\n";
					wss << L"Timer: " << m_fadeTimer << L"\n";
					wss << L"Progress: " << progress << L"\n";
					wss << L"Alpha: " << currentAlpha << L"\n";
				}
				else
				{
					stageSpr->SetDrawActive(false);
				}
			}
		}

	}

	void GameStage::OnPushA()
	{

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
		app->RegisterTexture(L"TEX_PAUSE", texPath + L"PauseSprite.png");
		app->RegisterTexture(L"TEX_NEZUMI", texPath + L"nezumi.png");
		app->RegisterTexture(L"TEX_NEZUMI2", texPath + L"nezumi2.png");
		app->RegisterTexture(L"TEX_SHELF", texPath + L"Shelf.png");
		app->RegisterTexture(L"TEX_ENEMY", texPath + L"Cat.png");
		app->RegisterTexture(L"TEX_START", texPath + L"Goal.png");
		app->RegisterTexture(L"TEX_GOAL", texPath + L"Goal.png");
		app->RegisterTexture(L"TEX_BbuttondeGameStart", texPath + L"BbuttondeGameStart.png");
		app->RegisterTexture(L"TEX_RESTART", texPath + L"PauseStage restart.png");
		app->RegisterTexture(L"TEX_BACK", texPath + L"PauseStage title.png");
		app->RegisterTexture(L"TEX_SETTING", texPath + L"PauseStage setting.png");
		app->RegisterTexture(L"TEX_END", texPath + L"PauseStage end.png");
		app->RegisterTexture(L"TEX_END2", texPath + L"PauseStage Back.png");

		app->RegisterTexture(L"TEX_GameStageUI", texPath + L"GameStageUI.png");
		app->RegisterTexture(L"TEX_GameButtonUI", texPath + L"GameButtonUI.png");
		app->RegisterTexture(L"TEX_Filter", texPath + L"Filter.png");


	}

	void GameStage::LoadModels()
	{
		auto& app = App::GetApp();

		auto mediaPath = app->GetDataDirWString();

		auto modelPath = mediaPath + L"Models\\";


		//ランプ
		if (app->CheckResource<MeshResource>(L"MODEL_LAMP")) return;
		auto meshLamp = MeshResource::CreateStaticModelMesh(modelPath + L"Lamp\\", L"NyauNyauLamp.bmf");
		app->RegisterResource(L"MODEL_LAMP", meshLamp);


		//テーブル
		if (app->CheckResource<MultiMeshResource>(L"MODEL_TABLE")) return;
		auto meshTable = MultiMeshResource::CreateStaticModelMultiMesh(modelPath + L"Table\\", L"Table.bmf");
		app->RegisterResource(L"MODEL_TABLE", meshTable);


		//つみき(青)
		if (app->CheckResource<MeshResource>(L"MODEL_TSUMIKI1")) return;
		auto meshTsumiki1 = MeshResource::CreateBoneModelMesh(modelPath + L"Block1\\", L"Block1.bmf");
		app->RegisterResource(L"MODEL_TSUMIKI1", meshTsumiki1);

	}


	void GameStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);

	}

	void GameStage::OnUpdate2()
	{
		/*	auto& app = App::GetApp();
			MainCamera* mainCam = app->*/

		if (currentPhase == GamePhase::Phase1)
		{

			auto pause = m_pauseManager.lock();
			if (!pause)
			{
				return;
			}

			if (pause->IsPlaying())
			{
				auto gameObjectVec = GetGameObjectVec();
				for (auto obj : gameObjectVec)
				{

					/*if (gameObjectVec.empty())
					{
						std::cout << "GetGameObjectVec() によって取得されたオブジェクトのリストが空です。" << std::endl;
						return;
					}*/
					if (dynamic_pointer_cast<PauseManager>(obj))
					{
						obj->SetUpdateActive(true);
					}

					if (dynamic_pointer_cast<Box>(obj)) //dynamic_pointer_cast<Box>(obj) 
					{
						obj->SetUpdateActive(true);
					}
					else if (dynamic_pointer_cast<ShadowObject>(obj))
					{
						obj->SetUpdateActive(true);
					}
					else
					{
						obj->SetUpdateActive(false);
					}


				}



				auto pause = m_pauseManager.lock();
				if (!pause)
				{
					return;
				}

				// BボタンでPhase2(GameStart)へ
				auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
				{
					SetView(m_mainView);

					currentPhase = GamePhase::Phase2;

					auto UI = m_gameStageUI[0].lock();
					UI->SetDrawActive(false);

					auto gameObjectVec = GetGameObjectVec();
					for (auto obj : gameObjectVec)
					{
						if (dynamic_pointer_cast<Box>(obj))
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
	}
}
	
//end basecross
