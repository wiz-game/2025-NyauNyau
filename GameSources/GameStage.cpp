
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
		const Vec3 eye(20.0f, 10.0f, 10.0f);// 10,20,-8
		const Vec3 at(-3.0f,0.0f,0.0f);
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
		vector<vector<Vec3>> vec = {
			//{
			//	Vec3(30.0f, 10.0f, 1.0f), 
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, 4.0f, 5.0f)
			//},
			{
				Vec3(30.0f, 10.0f, 1.0f),
				Vec3(0.0f, -XM_PIDIV2,0.0f),
				Vec3(-5.30f, 4.0f, 0.0f)
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
			Vec3(20.0f, 1.0f, 30.0f),  // 10,1,10
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
			Vec3(0.1f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-4.7f,0.005f,-10.0f)
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
				Vec3(0.0f, 0.25f, 0.25f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-4.75f, 0.0f, -9.0f)
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
			Vec3(-4.7f,0.005f,10.0f)
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
			Vec3(0.002f,0.5f,0.7f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-4.75f,0.001f,2.0f)
		}
		};
		//オブジェクトの作成
		for (auto v : vec) {
			AddGameObject<Cheese>(v[0], v[1], v[2]);
		}
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
			auto box = AddGameObject<Box>();
			SetSharedGameObject(L"Box", box);
			//SpotLightの作成
			auto spotLight = AddGameObject<SpotLight>();
			SetSharedGameObject(L"SpotLight", spotLight);
			//影の作成
			AddGameObject<ShadowObject>();
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
			//レイの生成
			auto raycastLine = AddGameObject<RaycastLine>();
			SetSharedGameObject(L"RaycastLine", raycastLine);

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

	//ゲーム終了
	void GameStage::OnPushB()
	{
		if (m_PauseFlag)
		{
			PostQuitMessage(0);
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

		// テクスチャの読込と登録
		//app->RegisterTexture(L"TEX_BOX", texPath + L"brick.jpg");
		app->RegisterTexture(L"TEX_CHEESE", texPath + L"cheese.png");
		app->RegisterTexture(L"TEX_KABE", texPath + L"kabe.jpg");
		app->RegisterTexture(L"TEX_YUKA", texPath + L"yuka.jpg");
		app->RegisterTexture(L"TEX_PAUSE", texPath + L"pauseSprite.png");
	}

}
//end basecross
