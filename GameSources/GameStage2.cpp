
/*!
@file GameStage2.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

#include "ShadowDrawer.h"
#include "RaycastLine.h"
#include "SpotLight Of Effect.h"
namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage2::CreateViewLight()
	{

		m_mainView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrmainCamera = ObjectFactory::Create<MainCamera>();
		ptrmainCamera->SetEye(Vec3(12.0f, 0.0f, 10.0f));
		ptrmainCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_mainView->SetCamera(ptrmainCamera);

		m_phase1View = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrphase1Camera = ObjectFactory::Create<Phase1Camera>();
		ptrphase1Camera->SetEye(Vec3(10.0f, 30.0f, -70.0f));
		ptrphase1Camera->SetAt(Vec3(10.0f, 20.0f, 0.0f));
		m_phase1View->SetCamera(ptrphase1Camera);

		//OpeningCameraView用のビュー
		m_OpeningCameraView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrOpeningCamera = ObjectFactory::Create<OpeningCamera>();
		ptrOpeningCamera->SetEye(200.0f, 180.0f, 200.0f);
		m_OpeningCameraView->SetCamera(ptrOpeningCamera);

		//初期状態ではm_OpeningCameraViewを使う
		SetView(m_OpeningCameraView);
		m_CameraSelect = CameraSelect2::openingCamera;

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定

	}

	void GameStage2::CreateWall()
	{
		vector<vector<Vec3>> vec = {
			{
				Vec3(200.0f, 200.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 4.0f, 1.0f)
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

	void GameStage2::CreateGround()
	{
		vector<vector<Vec3>> vec = {
		{
			Vec3(200.0f, 10.0f, 200.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -10.0f, 0.0f)
		},

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

	void GameStage2::CreateShadowFloor()
	{
		vector<vector<Vec3>> vec = {
			//{
			//	Vec3(20.0f, 20.0f, 1.0f), 
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, 4.0f, 0.0f)
			//},
			//{   Vec3(50.0f, 5.0f, 1.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(40.0f, 30.0f, 0.0f)
			//},
			//{
			//	Vec3(70.0f, 5.0f, 1.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-50.0f, 40.0f, 0.0f)

	  //      },
			//{
			//	Vec3(100.0f, 50.0f, 1.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(55.0f, -3.0f, 0.0f)

	  //      },
			//{
			//	Vec3(40.0f, 30.0f, 1.0),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-25.0f, 5.0f, 0.0f)

			//},

		};

		int index = 0; // ユニーク名用のインデックス
		vector<shared_ptr<ShadowFloor>> shadowfloors; // 生成した `ShadowFloor` を管理するリスト

		for (auto& v : vec) {
			auto ptrShadowFloor = AddGameObject<ShadowFloor>(v[0], v[1], v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"ShadowFloor_" + to_wstring(index);

			ptrShadowFloor->AddTag(uniqueTag);  // ユニークなタグを適用
			shadowfloors.push_back(ptrShadowFloor);    // `ShadowFloor` をリストに保存

			index++; // 次のオブジェクトのためにインデックスを増加
		}

		// すべての `ShadowFloor` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < shadowfloors.size(); ++i) {
			wstring uniqueName = L"ShadowFloor_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, shadowfloors[i]);      // ユニーク名で共有登録
		}

	}

	//スタート
	void GameStage2::CreatestartGate()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.0f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-50.0f,0.005f,-0.5f)
		}
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<startGate>(v[0], v[1], v[2]);
		}
	}

	//プレイヤー
	void GameStage2::CreatePlayer()
	{
		vector<vector<Vec3>> vec =
		{
			{
				Vec3(1.25f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-35.0f, 22.0f, -0.5f)
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

		//players[0]->SetPlayerMove(false);
		//players[1]->SetPlayerMove(true);


		// すべての `Player` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < players.size(); i++)
		{
			wstring uniqueName = L"Player_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, players[i]);      // ユニーク名で共有登録

		}


	}

	void GameStage2::CreateEnemy()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(9.0f,9.0f,-0.001f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-55.0f,26.25f,-0.5f)
		}
		};
		for (auto& v : vec) {

			auto ptrEnemy = AddGameObject<Enemy>(v[0], v[1], v[2]);

		}
	}


	//ゴール
	void GameStage2::CreategoalGate()
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
	void GameStage2::CreateCheese()
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


	void GameStage2::CreateBox()
	{
		vector<vector<Vec3>> vec = {
		{
			Vec3(2.5f, 2.5f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(2.0f ,11.5f, -20.0f)
		},
		{
			Vec3(2.0f, 5.0f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(6.0f ,11.5f, -20.0f)
		},
		{
			Vec3(2.5f, 5.0f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(11.0f ,11.5f, -20.0f)
		},
		//{
		//	Vec3(2.5f, 5.0f, 2.5f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(17.0f ,11.5f, -20.0f)
		//},
		{
			Vec3(2.5f, 5.0f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(17.0f ,11.5f, -20.0f)
		},


		};

		int index = 0; // ユニーク名用のインデックス
		m_controllableBoxes.clear(); // 新しく生成する前にリストをクリア
		vector<shared_ptr<Box>> box; // 生成した `Box` を管理するリスト

		for (auto& v : vec) {
			auto ptrBox = AddGameObject<Box>(v[0], v[1], v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"Box_" + to_wstring(index);

			ptrBox->AddTag(uniqueTag);  // ユニークなタグを適用
			m_controllableBoxes.push_back(ptrBox);    // 生成したBoxをリストに追加
			box.push_back(ptrBox);    // `Box` をリストに保存
			wstring uniqueName = L"MODEL_TSUMIKI" + to_wstring(index + 1);

			if (index <= 1)
			{
				box[index]->GetComponent<PNTBoneModelDraw>()->SetMeshResource(uniqueName);
				index++; // 次のオブジェクトのためにインデックスを増加
			}
			else
			{
				index = 0;
			}
		}

		// すべての `Box` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < box.size(); ++i) {
			wstring uniqueName = L"Box_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, box[i]);      // ユニーク名で共有登録
		}

	}


	void GameStage2::CreateTable()
	{
		vector<vector<Vec3>> vec = {
		{
			Vec3(3.0f, 6.0f, 1.0f),
			Vec3(0.0f, XM_PIDIV2, 0.0f),
			Vec3(10.0f, -10.0f, -25.0f)
		}
		};

		vector<shared_ptr<Table>> table; // 生成した `Table` を管理するリスト

		for (auto& v : vec)
		{
			auto ptrTable = AddGameObject<Table>(v[0], v[1], v[2]);
			ptrTable->AddTag(L"Table");
			table.push_back(ptrTable);
		}

		SetSharedGameObject(L"Table", table[0]);      // ユニーク名で共有登録


	}

	void GameStage2::CreateMado()
	{
		vector<vector<Vec3>> vec = {
			{   Vec3(20.0f, 24.4f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(60.0f, 37.0f, 0.0f)
			},

		};


		int index = 0; // ユニーク名用のインデックス
		vector<shared_ptr<Window>> windows; // 生成した `Window` を管理するリスト

		for (auto& v : vec) {
			auto ptrWindow = AddGameObject<Window>(v[0], v[1], v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"Window_" + to_wstring(index);

			ptrWindow->AddTag(uniqueTag);  // ユニークなタグを適用
			windows.push_back(ptrWindow);    // `Window` をリストに保存

			index++; // 次のオブジェクトのためにインデックスを増加
		}

		// すべての `Window` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < windows.size(); ++i) {
			wstring uniqueName = L"Window_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, windows[i]);      // ユニーク名で共有登録
		}

	}

	void GameStage2::CreateBookShelf()
	{
		vector<vector<Vec3>> vec = {
			{   Vec3(40.0f, 25.0f, 1.0f),
				Vec3(0.0f, XMConvertToRadians(180), 0.0f),
				Vec3(74.0f, 2.0f, 0.0f)
			},
			{
				Vec3(40.0f, 30.0f, 1.0f),
				Vec3(0.0f, XMConvertToRadians(180), 0.0f),
				Vec3(-37.0f, 4.0f, 0.0f)
			},
			//{
			//	Vec3(20.0f, 30.0f, 1.0f),
			//	Vec3(0.0f, XMConvertToRadians(180), 0.0f),
			//	Vec3(60.0f, 37.0f, 0.0f)
			//},
			{   Vec3(20.0f, 40.0f, 1.0f),
				Vec3(0.0f, XMConvertToRadians(180), 0.0f),
				Vec3(28.0f, 5.0f, 0.0f)
			},

		};


		int index = 0; // ユニーク名用のインデックス
		vector<shared_ptr<BookShelf>> bookshelfs; // 生成した `BookShelf` を管理するリスト

		for (auto& v : vec) {
			auto ptrBookShelf = AddGameObject<BookShelf>(v[0], v[1], v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"BookShelf_" + to_wstring(index);

			ptrBookShelf->AddTag(uniqueTag);  // ユニークなタグを適用
			bookshelfs.push_back(ptrBookShelf);    // `BookShelf` をリストに保存

			index++; // 次のオブジェクトのためにインデックスを増加
		}

		// すべての `BookShelf` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < bookshelfs.size(); ++i) {
			wstring uniqueName = L"BookShelf_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, bookshelfs[i]);      // ユニーク名で共有登録
		}

	}


	//カメラマンの作成
	void GameStage2::CreateCameraman()
	{
		auto ptrOpeningCameraman = AddGameObject<OpeningCameraman>();
		//シェア配列にOpeningCameramanを追加
		SetSharedGameObject(L"OpeningCameraman", ptrOpeningCameraman);

		auto ptrOpeningCamera = dynamic_pointer_cast<OpeningCamera>(m_OpeningCameraView->GetCamera());
		if (ptrOpeningCamera)
		{
			ptrOpeningCamera->SetCameraObject(ptrOpeningCameraman);
			SetView(m_OpeningCameraView);
			m_CameraSelect = CameraSelect2::openingCamera;
		}

	}

	void GameStage2::CreateSpotLight()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.25f,0.25f,0.25f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(10.0f,12.0f,-30.0f),
		}
		};
		int index = 0; // ユニーク名用のインデックス
		vector<shared_ptr<SpotLight>> spotLights; // 生成した `Window` を管理するリスト

		for (auto& v : vec) {
			auto ptrSpotLight = AddGameObject<SpotLight>(v[0], v[1], v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"SpotLight_" + to_wstring(index);

			ptrSpotLight->AddTag(uniqueTag);  // ユニークなタグを適用
			spotLights.push_back(ptrSpotLight);    // `Window` をリストに保存

			index++; // 次のオブジェクトのためにインデックスを増加
		}

		// すべての `Window` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < spotLights.size(); ++i) {
			wstring uniqueName = L"SpotLight_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, spotLights[i]);      // ユニーク名で共有登録
		}
	}

	void GameStage2::OnCreate() {
		try {

			LoadTextures();
			LoadModels();


			//ビューとライトの作成
			CreateViewLight();
			//壁の作成
			CreateWall();
			//ステージの作成
			CreateGround();
			//シャドウフロアの作成
			CreateShadowFloor();
			//テーブルの作成
			CreateTable();
			//Boxの作成
			CreateBox();
			//ShadowBall(ギミック)の作成
			//CreateShadowBall();
			//SpotLightの作成
			auto spotLight = AddGameObject<SpotLight>();
			SetSharedGameObject(L"SpotLight", spotLight);
			//影の作成
			//AddGameObject<ShadowObject>();
			auto shadowDrawer = AddGameObject<ShadowDrawer>();
			SetSharedGameObject(L"ShadowDrawer", shadowDrawer);
			//プレイヤーの作成
			CreatePlayer();
			//エネミーの作成
			CreateEnemy();
			//スタートの作成
			CreatestartGate();
			//ゴールの作成
			//CreategoalGate();
			AddGameObject<goalGate>(
				Vec3(2.5f, 3.5f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(57.0f, 16.0f, -0.1f)
			);

			//ねこの助走用の足場
			AddGameObject<ShadowFloor>(
				Vec3(100.0f, 30.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-75.0f, 4.0f, 0.0f)
			);

			//チーズの作成
			CreateCheese();
			//本棚の作成
			CreateBookShelf();
			//窓の作成
			CreateMado();
			//カメラマンの作成
			CreateCameraman();



			//スプライトオブジェクト
			AddGameObject<Phase1>();

			//auto UI = AddGameObject<GameStageUI>();
			//UI->SetTexture(L"TEX_GameStageUI");
			//UI->SetPosition(0, 300.0f, 0);
			//UI->SetScale(2.0f, 1.0f, 1.0f);
			//m_gameStageUI.push_back(UI);

			//コントローラUI
			auto phase1UI_A = AddGameObject<GameStageUI>();
			phase1UI_A->SetTexture(L"TEX_phase1UI_A");
			phase1UI_A->SetPosition(535.0f, -280.0f, 0);
			phase1UI_A->SetScale(0.5f, 0.4f, 1.0f);
			phase1UI_A->SetDrawActive(true);
			m_gameStageUI.push_back(phase1UI_A);

			auto phase1UI_B = AddGameObject<GameStageUI>();
			phase1UI_B->SetTexture(L"TEX_phase1UI_B");
			phase1UI_B->SetPosition(530.0f, -200.0f, 0);
			phase1UI_B->SetScale(0.5f, 0.4f, 1.0f);
			phase1UI_B->SetDrawActive(true);
			m_gameStageUI.push_back(phase1UI_B);

			auto phase1UI_light = AddGameObject<GameStageUI>();
			phase1UI_light->SetTexture(L"TEX_phase1UI_light");
			phase1UI_light->SetPosition(540.0f, -360.0f, 0);
			phase1UI_light->SetScale(0.5f, 0.4f, 1.0f);
			phase1UI_light->SetDrawActive(true);
			m_gameStageUI.push_back(phase1UI_light);

			auto phase2UI_A = AddGameObject<GameStageUI>();
			phase2UI_A->SetTexture(L"TEX_phase2UI_A");
			phase2UI_A->SetPosition(535.0f, -280.0f, 0);
			phase2UI_A->SetScale(0.5f, 0.4f, 1.0f);
			phase2UI_A->SetDrawActive(false);
			m_gameStageUI.push_back(phase2UI_A);

			m_stageUI = AddGameObject<GameStageUI>();
			auto stage = m_stageUI.lock();
			stage->SetTexture(L"TEX_STAGE2");
			stage->SetPosition(0, 0, 0);
			stage->SetScale(2.0f, 2.0f, 1.0f);

			//プレイヤーに追尾するアセェ
			auto playerObject = GetSharedGameObject<Player>(L"Player_0");
			m_ase = AddGameObject<GameStagePointerUI>();
			auto ase = m_ase.lock();
			ase->SetTexture(L"TEX_Ase");
			ase->SetPosition(0, 0, 0);
			ase->SetScale(0.8f, 0.8f, 1.0f);
			ase->SetTargetPlayer(playerObject);



			m_selectionPointerUI = AddGameObject<GameStagePointerUI>();
			auto pointer = m_selectionPointerUI.lock();
			pointer->SetTexture(L"TEX_BoxPointer");
			pointer->SetScale(1.2f, 1.2f, 1.0f);
			pointer->SetDrawActive(true);
			pointer->SetTargetBox(m_controllableBoxes[0], true);

			//フェードスクリーンを生成して保持する
			auto fadeScreen = AddGameObject<FadeScreen>();
			m_fadeScreen = fadeScreen;

			auto scene = App::GetApp()->GetScene<Scene>();
			auto volume = scene->m_volumeBGM;

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Gamebgm", XAUDIO2_LOOP_INFINITE, volume);

			m_pauseManager = AddGameObject<PauseManager>();

			// 操作モードの初期設定
			m_currentControlMode = GameControlMode2::SelectBox; // ゲーム開始時はまずBoxを選択するモードから
			m_selectedBoxIndex = -1;                           // まだ何も選択候補になっていない状態を示す 
			m_currentlyControlledBox = nullptr;                // まだ操作対象のBoxは決定されていない

			m_stickMovedLeftLastFrame = false;   // 前のフレームで左に倒されていたか
			m_stickMovedRightLastFrame = false;  // 前のフレームで右に倒されていたか
			m_lastNotifiedIndex = -2;//UIはまだ通知されていない

			// もし操作可能なBoxがステージに存在すれば、最初のBoxを選択候補とする
			if (!m_controllableBoxes.empty())
			{
				m_selectedBoxIndex = 0; // 最初のBox (Box_0) を選択候補にする
			}


			// ---phase1の時間制限タイマーの初期化---
			m_isTimer = 0.0f;
			m_isTimerflag = true;

			// --- 最初の2秒間のタイマーの初期化 ---
			m_isShortTimer = 0.0f;     // タイマーを0にリセット
			m_isShortTimerflag = true;  // ゲーム開始直後なので、初期期間フラグをtrueに

			//タイマー時計UIの生成
			Vec2 clockPosition = Vec2(0.0f, 290.0f); // 時計を表示する位置
			// 時計の外枠のスケール
			float TimerFrameScaleX = 0.5f;
			float TimerFrameScaleY = 0.8f;
			//時計の文字盤（中）のスケール
			float TimerClockFaceScaleX = 0.5f;
			float TimerClockFaceScaleY = 0.8f;
			//時計の秒針のスケール
			float TimerSecHandScaleX = 0.5f;
			float TimerSecHandScaleY = 0.68f;

			// 時計の外枠
			auto clockFrame = AddGameObject<GameStageUI>();
			clockFrame->SetTexture(L"TEX_TimerFrame");
			clockFrame->SetPosition(clockPosition.x, clockPosition.y, 0.2f);
			clockFrame->SetScale(TimerFrameScaleX, TimerFrameScaleY, 1.0f);
			m_timerClockFrameUI = clockFrame;

			// 時計の文字盤
			auto clockFace = AddGameObject<GameStageUI>();
			clockFace->SetTexture(L"TEX_TimerClockFace");
			clockFace->SetPosition(clockPosition.x, clockPosition.y, 0.3f);
			clockFace->SetScale(TimerClockFaceScaleX, TimerClockFaceScaleY, 1.0f);
			m_timerClockFaceUI = clockFace;

			// 時計の秒針 
			auto clockHand = AddGameObject<GameStageUI>();
			clockHand->SetTexture(L"TEX_TimerSecHand");
			clockHand->SetPosition(clockPosition.x, clockPosition.y, 0.2f);
			clockHand->SetScale(TimerSecHandScaleX, TimerSecHandScaleY, 1.0f);
			m_timerSecHandUI = clockHand;

			//秒針のピボットを設定（画像の下の部分が中心になるようにする）
			auto sechandTransform = clockHand->GetComponent<Transform>();
			if (sechandTransform)
			{
				sechandTransform->SetPivot(Vec3(0.0f, -0.5f, 0.0f)); // Y軸方向にピボットをずらす
			}

			//タイマー
			clockFrame->SetDrawActive(false);
			clockFace->SetDrawActive(false);
			clockHand->SetDrawActive(false);

			isTimerSoundFlag = true;


			// オーラエフェクト（２つのオーラの大きさとアニメーションスピードを変えて重ねて表現）
			SpotLightOfEffect::InitParams params; // オーラエフェクトに渡すパラメータをまとめた構造体（BaseCrossはAddGameObjectの際、引数が分かりづらいのでまとめると良い）
			params.textureKey = L"line";//テクスチャ
			params.sides = 30;			//面の数
			params.height = 1.0f;		//筒の高さ
			params.topRadius = 1.0f;	//筒の上のわっかの半径
			params.bottomRadius = 1.0f; //下のわっかの半径
			params.topColor = Col4(0.0f, 1.0f, 0.0f, 0.0f);		//上の方の色
			params.bottomColor = Col4(0.5f, 1.0f, 0.0f, 1.0f);	//下の方の色
			params.uvOffsetSpeed = Vec2(0.1f, 0.0f);			//アニメーションの速さ(テクスチャをずらす)
			params.textureLoops = 1.0f;							//テクスチャのループ
			AddGameObject<SpotLightOfEffect>(params); // 1つ目のオーラ

			// ライト的なエフェクト
			auto light = AddGameObject<SpotLightOfEffect>(SpotLightOfEffect::InitParams(L"line", 30, 0.0f, 0.0f, 5.0f, Col4(1.0f, 1.0f, 1.0f, 1.0f), Col4(0.2f, 0.2f, 0.2f, 0.0f), Vec2(0.0f)));
			light->GetComponent<Transform>()->SetPosition(Vec3(10.0f, 11.2f, -30.0f));
		}
		catch (...) {
			throw;
		}
	}

	GameControlMode2 GameStage2::GetCurrentControlMode() const
	{
		return m_currentControlMode; // 現在の操作モードを返す
	}


	void GameStage2::OnUpdate()
	{

		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameStage2>());


		auto& app = App::GetApp();
		// コントローラーの状態を取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		// 最初のコントローラーが接続されているか確認
		if (cntlVec[0].bConnected)
		{
			// 現在の操作モードによって処理を分岐
			if (m_currentControlMode == GameControlMode2::SelectBox)
			{

				// 左スティックのX軸の値を取得
				float stickX = cntlVec[0].fThumbLX;

				// スティック入力が反応する値（この値より大きく倒されたら反応）
				const float stickThreshold = 0.8f;

				// --- 右への選択切り替え ---
				if (stickX > stickThreshold && !m_stickMovedRightLastFrame)
				{
					SelectNextBox(); // 次のBoxを選択候補に
					m_stickMovedRightLastFrame = true; // 右に倒されたことを記憶
				}
				// スティックが右から中央に戻り始めたら、フラグをリセットする準備
				else if (stickX <= stickThreshold && m_stickMovedRightLastFrame)
				{
					// 値を下回ったらリセットする
					m_stickMovedRightLastFrame = false;
				}

				// --- 左への選択切り替え ---
			   // スティックが左に一定以上倒されていて、かつ「前フレームでは左に倒されていなかった」場合
				if (stickX < -stickThreshold && !m_stickMovedLeftLastFrame)
				{
					SelectPreviousBox(); // 前のBoxを選択候補に
					m_stickMovedLeftLastFrame = true; // 左に倒されたことを記憶
				}
				// スティックが左から中央に戻り始めたら、フラグをリセットする準備
				else if (stickX >= -stickThreshold && m_stickMovedLeftLastFrame)
				{
					m_stickMovedLeftLastFrame = false;
				}

				// Aボタンが押されたら現在の選択候補を操作対象に決定しようとする
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{
					AttemptToControlSelectedBox();
				}
			}
			else if (m_currentControlMode == GameControlMode2::ControlBox)
			{
				//もう一度Aボタンが押されたらBoxの操作を終了し、SelectBoxモードに戻る
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{
					ReleaseControlOfBox();
				}
			}
		}

		UpdateSelectionUI();

		auto device = app->GetInputDevice();
		auto pad = device.GetControlerVec()[0];
		auto delta = app->GetElapsedTime();

		//auto scene = app->GetScene<Scene>();
		//wstring log = scene->GetDebugString();
		//wstringstream wss(log);


		m_Time += delta;

		if (m_Time > 0.3f && !m_isStageFadingOut)
		{
			m_isStageFadingOut = true;
		}

		if (m_isStageFadingOut)
		{
			//スプライトが有効で、まだ表示されていたら
			auto stageSpr = m_stageUI.lock();

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

				}
				else
				{
					stageSpr->SetDrawActive(false);

				}
			}
		}

	}

	void GameStage2::ToPhase1Camera()
	{
		//Phase1Cameraに変更
		auto ptrPhase1Camera = dynamic_pointer_cast<Phase1Camera>(m_phase1View->GetCamera());
		if (ptrPhase1Camera)
		{
			SetView(m_phase1View);
			m_CameraSelect = CameraSelect2::phase1Camera;
		}
	}


	void GameStage2::OnPushA()
	{

	}

	// 次のBoxを選択候補としてハイライトする関数
	void GameStage2::SelectNextBox()
	{
		// 現在がSelectBoxモードで、かつ操作可能なBoxが存在する場合のみ処理を行う
		if (m_currentControlMode != GameControlMode2::SelectBox || m_controllableBoxes.empty())
		{
			return;
		}

		// 選択候補のインデックスを次に進める
		m_selectedBoxIndex++;

		// インデックスがリストの末尾を超えたら、先頭に戻す (ループ選択)
		if (m_selectedBoxIndex >= m_controllableBoxes.size())
		{
			m_selectedBoxIndex = 0;
		}
	}

	// 前のBoxを選択候補としてハイライトする関数
	void GameStage2::SelectPreviousBox()
	{
		// 現在がSelectBoxモードで、かつ操作可能なBoxが存在する場合のみ処理を行う
		if (m_currentControlMode != GameControlMode2::SelectBox || m_controllableBoxes.empty())
		{
			return;
		}
		// 選択候補のインデックスを前に戻す
		m_selectedBoxIndex--;
	}

	// 現在ハイライトされているBoxを操作対象に設定し、ControlBoxモードへ移行する関数
	void GameStage2::AttemptToControlSelectedBox()
	{
		// 現在がSelectBoxモードで、かつ有効なBoxが選択候補になっている場合のみ処理を行う
		if (m_currentControlMode == GameControlMode2::SelectBox &&
			m_selectedBoxIndex >= 0 && m_selectedBoxIndex < m_controllableBoxes.size())
		{
			// 選択候補のBoxを操作対象として設定
			m_currentlyControlledBox = m_controllableBoxes[m_selectedBoxIndex];
			if (m_currentlyControlledBox)
			{
				// Boxオブジェクト自体に「自分が操作対象である」ことを通知する
				m_currentlyControlledBox->SetSelectedForControl(true);
				// ゲームの操作モードをControlBoxモードに切り替える
				m_currentControlMode = GameControlMode2::ControlBox;

				//操作可能のボックスとポインターを親子関係にする
				if (auto point = m_selectionPointerUI.lock())
				{
					point->SetTargetBox(m_controllableBoxes[m_selectedBoxIndex], false);
				}

			}
		}
	}

	// Boxの操作を終了し、SelectBoxモードへ戻る関数
	void GameStage2::ReleaseControlOfBox()
	{
		// 現在がControlBoxモードの場合のみ処理を行う
		if (m_currentControlMode == GameControlMode2::ControlBox)
		{
			// もし現在操作中のBoxがあれば、そのBoxに「操作対象でなくなった」ことを通知する
			if (m_currentlyControlledBox)
			{
				m_currentlyControlledBox->SetSelectedForControl(false);
				m_currentlyControlledBox = nullptr; // 操作対象のポインタをクリア
			}
		}
		// ゲームの操作モードをSelectBoxモードに戻す
		m_currentControlMode = GameControlMode2::SelectBox;
	}

	std::shared_ptr<Table> GameStage2::GetTableObject() const
	{
		return GetSharedGameObject<Table>(L"Table");
	}


	void GameStage2::UpdateSelectionUI()
	{
		int currentTargetIndex = -1;

		// 現在のモードからターゲットにすべきBoxのインデックスを決定
		if (m_currentControlMode == GameControlMode2::SelectBox)
		{
			currentTargetIndex = m_selectedBoxIndex;
		}
		else if (m_currentControlMode == GameControlMode2::ControlBox)
		{
			if (m_currentlyControlledBox)
			{
				for (int i = 0; i < m_controllableBoxes.size(); ++i)
				{
					if (m_controllableBoxes[i] == m_currentlyControlledBox)
					{
						currentTargetIndex = i;
						break;
					}
				}
			}
		}

		// ターゲットが前回から変更された場合のみ、UIに通知する
		if (currentTargetIndex != m_lastNotifiedIndex)
		{
			if (auto pointer = m_selectionPointerUI.lock())
			{
				bool shouldAnimate = (m_currentControlMode == GameControlMode2::SelectBox);

				if (currentTargetIndex >= 0 && currentTargetIndex < m_controllableBoxes.size())
				{
					pointer->SetTargetBox(m_controllableBoxes[currentTargetIndex], shouldAnimate);
				}
				else
				{
					pointer->SetTargetBox(nullptr, false);
				}
			}
			m_lastNotifiedIndex = currentTargetIndex;
		}
	}


	void GameStage2::OnPlayerCollision(shared_ptr<GameObject> player, shared_ptr<GameObject> other)
	{
	}

	// ゲームオーバー処理（フェードとシーン遷移）に特化した関数
	void GameStage2::StartGameOver()
	{
	}


	// テクスチャの読込
	void GameStage2::LoadTextures()
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
		app->RegisterTexture(L"TEX_KABE", texPath + L"kabe2.png");
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
		app->RegisterTexture(L"TEX_phase1UI_A", texPath + L"phase1UI_A.png");
		app->RegisterTexture(L"TEX_phase1UI_B", texPath + L"phase1UI_B.png");
		app->RegisterTexture(L"TEX_phase1UI_light", texPath + L"phase1.2UI_light.png");
		app->RegisterTexture(L"TEX_phase2UI_A", texPath + L"phase2UI_A.png");
		app->RegisterTexture(L"TEX_BoxPointer", texPath + L"BoxPoint.png");
		app->RegisterTexture(L"TEX_Exclamationmark", texPath + L"Exclamationmark.png");
		app->RegisterTexture(L"TEX_TimerFrame", texPath + L"Timer.png");
		app->RegisterTexture(L"TEX_TimerClockFace", texPath + L"WhiteCircle.png");
		app->RegisterTexture(L"TEX_TimerSecHand", texPath + L"sechand.png");
		//app->RegisterTexture(L"TEX_Exclamationmark", texPath + L"Exclamationmark.png");
		app->RegisterTexture(L"TEX_Ase", texPath + L"Ase.png");
		app->RegisterTexture(L"line", texPath + L"line.png"); // 画像ファイルを読み込んでアセットとして登録する

	}

	void GameStage2::LoadModels()
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


		//本棚
		if (app->CheckResource<MultiMeshResource>(L"MODEL_BOOKSHELF")) return;
		auto meshBookShelf = MultiMeshResource::CreateStaticModelMultiMesh(modelPath + L"BookShelf\\", L"BookShelf.bmf");
		app->RegisterResource(L"MODEL_BOOKSHELF", meshBookShelf);


		//窓
		if (app->CheckResource<MultiMeshResource>(L"MODEL_WINDOW")) return;
		auto meshWindow = MultiMeshResource::CreateStaticModelMultiMesh(modelPath + L"Window\\", L"Window.bmf");
		app->RegisterResource(L"MODEL_WINDOW", meshWindow);


		//つみき(青/立方体)
		if (app->CheckResource<MeshResource>(L"MODEL_TSUMIKI1")) return;
		auto meshTsumiki1 = MeshResource::CreateBoneModelMesh(modelPath + L"Block1\\", L"Block1.bmf");
		app->RegisterResource(L"MODEL_TSUMIKI1", meshTsumiki1);


		//つみき(赤/立方体)
		if (app->CheckResource<MeshResource>(L"MODEL_TSUMIKI2")) return;
		auto meshTsumiki2 = MeshResource::CreateBoneModelMesh(modelPath + L"Block2\\", L"Block2.bmf");
		app->RegisterResource(L"MODEL_TSUMIKI2", meshTsumiki2);


		//つみき(黄/四角推)
		if (app->CheckResource<MeshResource>(L"MODEL_TSUMIKI3")) return;
		auto meshTsumiki3 = MeshResource::CreateBoneModelMesh(modelPath + L"Block3\\", L"Block3.bmf");
		app->RegisterResource(L"MODEL_TSUMIKI3", meshTsumiki3);


		//つみき(緑/三角錐)
		if (app->CheckResource<MeshResource>(L"MODEL_TSUMIKI4")) return;
		auto meshTsumiki4 = MeshResource::CreateBoneModelMesh(modelPath + L"Block4\\", L"Block4.bmf");
		app->RegisterResource(L"MODEL_TSUMIKI4", meshTsumiki4);


		//ねこ
		if (app->CheckResource<MeshResource>(L"MODEL_NEKO")) return;
		auto meshNeko = MeshResource::CreateBoneModelMesh(modelPath + L"Neko\\", L"Neko.bmf");
		app->RegisterResource(L"MODEL_NEKO", meshNeko);

	}


	void GameStage2::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);

	}

	void GameStage2::OnUpdate2()
	{
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto scene = App::GetApp()->GetScene<Scene>();
		auto volume = scene->m_volumeBGM;
		auto volumeSE = scene->m_volumeSE;
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		auto gameObjectVec = GetGameObjectVec();

		// 時計の各パーツのポインタを取得
		auto clockFrame = m_timerClockFrameUI.lock();
		auto clockFace = m_timerClockFaceUI.lock();
		auto clockHand = m_timerSecHandUI.lock();
		//ポーズ
		auto pause = m_pauseManager.lock();

		if (currentPhase == GamePhase2::Phase0)
		{
			if (!pause)
			{
				return;
			}

			m_isShortTimer += App::GetApp()->GetElapsedTime(); //タイマーの値をプラスしていく

			// --- 最初の2秒間のタイマー処理 ---
			if (m_isShortTimerflag)
			{
				if (pause->IsPlaying())
				{

					for (auto obj : gameObjectVec)
					{
						if (dynamic_pointer_cast<Player>(obj))
						{
							obj->SetUpdateActive(true);
						}
						else if (dynamic_pointer_cast<Enemy>(obj))
						{
							obj->SetUpdateActive(true);
						}
						else if (dynamic_pointer_cast<Box>(obj))
						{
							obj->SetUpdateActive(false);
						}
						else if (dynamic_pointer_cast<PauseManager>(obj))
						{
							obj->SetUpdateActive(true);
						}
						else
						{
							obj->SetUpdateActive(true);
						}
					}
				}
				if (m_isShortTimer >= 2.0f)
				{
					m_isShortTimerflag = false;
					currentPhase = GamePhase2::Phase1;
				}
			}
			//UIの非表示
			NotUIDraw();
		}


		if (currentPhase == GamePhase2::Phase1)
		{
			if (!pause)
			{
				return;
			}

			//コントローラUIの表示
			CntlUIDraw();
			//フェーズ２の時のUIだけ非表示
			auto stagesr = m_gameStageUI[3].lock();
			stagesr->SetDrawActive(false);


			// ---phase1の時間制限のタイマー処理---
			if (m_isTimerflag)
			{
				m_isTimer += App::GetApp()->GetElapsedTime(); //タイマーの値をプラスしていく

				if (isTimerSoundFlag)
				{
					if (m_isTimer >= 26.0f) //残り10秒のタイミングを知らせる効果音を流す
					{
						auto scene = App::GetApp()->GetScene<Scene>();
						auto volume = scene->m_volumeBGM;
						auto ptrXA = App::GetApp()->GetXAudio2Manager();
						m_TimerSound = ptrXA->Start(L"Tikutaku", 0, 0.8f);
						isTimerSoundFlag = false;
					}
				}

				if (m_isTimer >= 36.0f) //時間制限を30秒にする
				{
					m_isTimerflag = false;
				}
			}

			for (auto obj : gameObjectVec)
			{
				//---phase1時のオブジェクト処理---
				if (m_isTimerflag)
				{
					if (pause->IsPlaying())
					{

						if (dynamic_pointer_cast<Box>(obj))
						{
							obj->SetUpdateActive(true);
						}
						else if (dynamic_pointer_cast<PauseManager>(obj))
						{
							obj->SetUpdateActive(true);
						}
						else if (dynamic_pointer_cast<ShadowDrawer>(obj))
						{
							obj->SetUpdateActive(true);
						}
						else if (dynamic_pointer_cast<OpeningCamera>(obj))
						{
							obj->SetUpdateActive(true);
						}
						else if (dynamic_pointer_cast<OpeningCameraman>(obj))
						{
							obj->SetUpdateActive(true);
						}
						else
						{
							obj->SetUpdateActive(false);
						}
					}

				}

			}

			// タイマーを表示して秒針を回転させる
			if (clockFrame && clockFace && clockHand)
			{
				if (m_isTimer >= 6.0f)
				{
					// UIを表示状態にする
					clockFrame->SetDrawActive(true);
					clockFace->SetDrawActive(true);
					clockHand->SetDrawActive(true);
					// 秒針の回転角度を計算(何フレーム(秒)で一周するか)
					float totalDuration = 30.0f;
					// 現在の時間の進捗率 (0.0 ～ 1.0) を計算
					float progress = (m_isTimer - 6.0f) / totalDuration; // 最初のカメラ演出の秒数分をマイナスしておく
					// 時計回りなのでマイナス方向
					float rotationAngleZ_degrees = -360.0f * progress;
					// ラジアンに変換
					float rotationAngleZ_radians = XMConvertToRadians(rotationAngleZ_degrees);
					// 秒針のTransformを取得して回転を設定
					auto handTransform = clockHand->GetComponent<Transform>();
					if (handTransform)
					{
						handTransform->SetRotation(Vec3(0.0f, 0.0f, rotationAngleZ_radians));
					}
				}
			}
			else
			{
				// 時間切れになったら時計を非表示にする
				if (auto clockHand = m_timerSecHandUI.lock()) clockHand->SetDrawActive(false);
				if (auto clockFace = m_timerClockFaceUI.lock()) clockFace->SetDrawActive(false);
				if (auto clockFrame = m_timerClockFrameUI.lock()) clockFrame->SetDrawActive(false);
			}

			//NotUIDraw();
			////コントローラチェックがfalesならキーボードUIを表示する
			//if (!CntlCheck)
			//{
			//	//キーボードUI
			//	auto KeyboardUI = m_gameStageUI_Key[3].lock();
			//	KeyboardUI->SetDrawActive(true);
			//}

			//if (cntlVec[0].wPressedButtons)
			//{
			//コントローラUI
			//auto UI = m_gameStageUI[3].lock();
			//UI->SetDrawActive(true);

			// Bボタン、もしくは制限時間オーバーでPhase2(GameStart)へ
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B || m_isTimerflag == false)
			{
				ptrXA->Start(L"Bbutton", 0, volumeSE);

				SetView(m_mainView);

				currentPhase = GamePhase2::Phase2;

				//UIの非表示
				NotUIDraw();
				//ジャンプのUIだけ表示する
				auto UI = m_gameStageUI[3].lock();
				UI->SetDrawActive(true);
				UI->SetPosition(540.0f, -360.0f, 0);
			}

		}

		if (currentPhase == GamePhase2::Phase2)
		{
			isTimerSoundFlag = false;
			ptrXA->Stop(m_TimerSound);

			// Phase2 になったら時計を非表示にする
			if (auto clockHand = m_timerSecHandUI.lock()) clockHand->SetDrawActive(false);
			if (auto clockFace = m_timerClockFaceUI.lock()) clockFace->SetDrawActive(false);
			if (auto clockFrame = m_timerClockFrameUI.lock()) clockFrame->SetDrawActive(false);

			if (pause->IsPlaying())
			{
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

	void GameStage2::CntlUIDraw()
	{
		//コントローラスプライトの表示
		for (int i = 0; i < m_gameStageUI.size(); i++)
		{
			auto stagesr = m_gameStageUI[i].lock();
			stagesr->SetDrawActive(true);
		}
	}



	void GameStage2::NotUIDraw()
	{
		//コントローラスプライトの表示
		for (int i = 0; i < m_gameStageUI.size(); i++)
		{
			auto stagesr = m_gameStageUI[i].lock();
			stagesr->SetDrawActive(false);
		}
	}


	void GameStage2::Reset()
	{
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto scene = App::GetApp()->GetScene<Scene>();


		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_BACK)
		{
			PostEvent(0.0f, GetThis<GameStage>(), scene, L"ToTitleStage");
		}
	}

}

//end basecross
