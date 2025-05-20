
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
				Vec3(80.0f, 10.0f, 1.0f),
				Vec3(0.0f,-XM_PIDIV2, 0.0f),
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
		SetSharedGameObject(L"Box",ptrBox);
		//タグをつける
		//ptrBox->AddTag(L"Box");
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



		}
		catch (...) {
			throw;
		}
	}
	void GameStage::OnUpdate()
	{

		//コントローラチェックして入力があればコマンド呼び出し
		//m_InputHandler.PushHandle(GetThis<GameStage>());
		//auto& app = App::GetApp();
		//auto device = app->GetInputDevice();
		//auto pad = device.GetControlerVec()[0];
		
		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();


		//スタートボタンを押したときにボーズする
		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START)
		{

			auto scene = App::GetApp()->GetScene<Scene>();
			int StageNum = scene->GetStageNum();
			scene->PauseGame();
			m_PauseFlag = !m_PauseFlag;

			if (m_PauseFlag)
			{
				m_Pause = AddGameObject<pauseSprite>();
				m_pauseSprite = true;


				if (CntlVec[0].bConnected)
				{
					//Aボタンを押したときにゲームステージに移動する
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
					{
						PostEvent(0.0f, GetThis<SelectStage>(), scene, L"ToGameStage");
						return;
					}

					//CntrolLock = falseの時
					if (!m_CntrolLock)
					{
						//上向き
						if (CntlVec[0].fThumbLY >= 0.8f)
						{
							StageNum--;
							//ステージ１より上にスティックを動かしたらステージ３に移動
							if (StageNum < 0)
							{
								StageNum = 2;
							}
							m_CntrolLock = true;
							scene->SetStageNum(StageNum);
							ChangeSelect(StageNum);
							//SetSelectYPosition(StageNum);
							//ポイントスプライトの座標変更

							if (leftPointSprite)
							{
								leftPointSprite->SetPosition(-250.0f, m_select, 0);
							}

						}
						//下向き
						else if (CntlVec[0].fThumbLY <= -0.8f)
						{
							StageNum++;
							//ステージ３に来たらステージ１に戻る
							if (StageNum >= 3)
							{
								StageNum = 0;
							}
							m_CntrolLock = true;
							scene->SetStageNum(StageNum);
							ChangeSelect(StageNum);
							//SetSelectYPosition(StageNum);
							//ポイントスプライトの座標変更
							if (leftPointSprite)
							{
								leftPointSprite->SetPosition(-250.0f, m_select, 0);
							}
						}

					}
					//動かしていない時
					else
					{
						if (CntlVec[0].fThumbLY == 0.0f)
						{
							m_CntrolLock = false;
						}
					}
				}

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

	//選択しているSpriteを点滅させる処理
	void GameStage::ChangeSelect(int num)
	{
		for (int i = 0; i < 3; i++)
		{
			std::shared_ptr<pauseSprite> srptr = m_pauseSprites[i].lock();
			if (srptr)
			{
				//StageNumがm_pauseSpritesと一致していたら
				if (i == num)
				{
					srptr->SetSelected(true);

				}
				else
				{
					srptr->SetSelected(false);
				}
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



	}

	void GameStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}


}
//end basecross
