
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
			Vec3(-50.0f,0.005f,-0.5f)
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
				Vec3(-25.0f, 21.0f, -0.5f)
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
		//	Vec3(4.0f, -4.75f, -4.0f)
  //      },
		{
			Vec3(2.5f, 2.5f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(-4.0f, -4.75f, -4.0f)
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


	void GameStage::CreateShadowBall()
	{
		vector<vector<Vec3>> vec = {
		{
			Vec3(3.0f, 3.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(29.0f , 40.0f, -0.01f)
		},
		{
			Vec3(3.0f, 3.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(-20.0f, 45.0f, -0.01f)
		},
		//{
		//	Vec3(2.5f, 2.5f, 0.0f),
		//	Vec3(0.0f, 0.0f, 0.0f),
		//	Vec3(-4.0f, -4.75f, -4.0f)
		//},


		};

		int index = 0; // ユニーク名用のインデックス
		vector<shared_ptr<ShadowBall>> ball; // 生成した `Ball` を管理するリスト

		for (auto& v : vec) 
		{
			auto ptrBall = AddGameObject<ShadowBall>(v[0], v[1], v[2]);

			// ユニーク名を生成
			wstring uniqueTag = L"Ball_" + to_wstring(index);

			ptrBall->AddTag(uniqueTag);  // ユニークなタグを適用
			ball.push_back(ptrBall);    // `Ball` をリストに保存

			index++; // 次のオブジェクトのためにインデックスを増加

		}

		// すべての `Ball` を共有ゲームオブジェクトとして登録
		for (size_t i = 0; i < ball.size(); ++i) {
			wstring uniqueName = L"Ball_" + to_wstring(i);  // ユニーク名を生成
			SetSharedGameObject(uniqueName, ball[i]);      // ユニーク名で共有登録
		}

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

			//ステージの見た目(ガチ雑スクリプトのため後で消す)
			AddGameObject<ShadowFloor>(
				Vec3(50.0f, 5.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(40.0f, 30.0f, 0.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(70.0f, 5.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-50.0f, 40.0f, 0.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(100.0f, 50.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(85.0f, -3.0f, 0.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(40.0f, 30.0f, 1.0),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-25.0f, 5.0f, 0.0f)
			);
			//AddGameObject<ShadowFloor>(
			//	Vec3(1.0f, 15.0f, 5.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-5.0f, -8.5f, 5.0f)
			//);
			//AddGameObject<ShadowFloor>(
			//	Vec3(1.0f, 17.0f, 5.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-5.0f, -8.5f, 15.0f)
			//);
			//AddGameObject<ShadowFloor>(
			//	Vec3(1.0f, 20.0f, 20.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-5.0f, -8.5f, 25.0f)
			//);




			AddGameObject<Table>(
				Vec3(3.0f, 6.0f, 1.0f),
				Vec3(0.0f, XM_PIDIV2, 0.0f),
				Vec3(10.0f, -6.0f, -25.0f)
			);


			//Boxの作成
			CreateBox();

			CreateShadowBall();

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

			// 操作モードの初期設定
			m_currentControlMode = GameControlMode::SelectBox; // ゲーム開始時はまずBoxを選択するモードから
			m_selectedBoxIndex = -1;                           // まだ何も選択候補になっていない状態を示す 
			m_currentlyControlledBox = nullptr;                // まだ操作対象のBoxは決定されていない

			m_stickMovedLeftLastFrame = false;   // 前のフレームで左に倒されていたか
			m_stickMovedRightLastFrame = false;  // 前のフレームで右に倒されていたか


			// もし操作可能なBoxがステージに存在すれば、最初のBoxを選択候補とする
			if (!m_controllableBoxes.empty()) 
			{
				m_selectedBoxIndex = 0; // 最初のBox (Box_0) を選択候補にする
			}

		}
		catch (...) {
			throw;
		}
	}

	GameControlMode GameStage::GetCurrentControlMode() const 
	{
		return m_currentControlMode; // 現在の操作モードを返す
	}


	void GameStage::OnUpdate()
	{

		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameStage>());


		auto& app = App::GetApp();
		// コントローラーの状態を取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		// 最初のコントローラーが接続されているか確認
		if (cntlVec[0].bConnected) 
		{
			// 現在の操作モードによって処理を分岐
			if (m_currentControlMode == GameControlMode::SelectBox) 
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
			else if (m_currentControlMode == GameControlMode::ControlBox)
			{
				//もう一度Aボタンが押されたらBoxの操作を終了し、SelectBoxモードに戻る
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) 
				{
					ReleaseControlOfBox();
				}
			}
		}
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

	// 次のBoxを選択候補としてハイライトする関数
	void GameStage::SelectNextBox() 
	{
		// 現在がSelectBoxモードで、かつ操作可能なBoxが存在する場合のみ処理を行う
		if (m_currentControlMode != GameControlMode::SelectBox || m_controllableBoxes.empty()) 
		{
			return;
		}

		// 選択候補のインデックスを次に進める
		m_selectedBoxIndex++;

		// インデックスがリストの末尾を超えたら、先頭に戻す (ループ選択)
		if (m_selectedBoxIndex >= m_controllableBoxes.size()) {
			m_selectedBoxIndex = 0;
		}
	}

	// 前のBoxを選択候補としてハイライトする関数
	void GameStage::SelectPreviousBox() 
	{
		// 現在がSelectBoxモードで、かつ操作可能なBoxが存在する場合のみ処理を行う
		if (m_currentControlMode != GameControlMode::SelectBox || m_controllableBoxes.empty()) {
			return;
		}
		// 選択候補のインデックスを前に戻す
		m_selectedBoxIndex--;
	}

	// 現在ハイライトされているBoxを操作対象に設定し、ControlBoxモードへ移行する関数
	void GameStage::AttemptToControlSelectedBox()
	{
		// 現在がSelectBoxモードで、かつ有効なBoxが選択候補になっている場合のみ処理を行う
		if (m_currentControlMode == GameControlMode::SelectBox &&
			m_selectedBoxIndex >= 0 && m_selectedBoxIndex < m_controllableBoxes.size())
		{
			// 選択候補のBoxを操作対象として設定
			m_currentlyControlledBox = m_controllableBoxes[m_selectedBoxIndex];
			if (m_currentlyControlledBox)
			{
				// Boxオブジェクト自体に「自分が操作対象である」ことを通知する
				m_currentlyControlledBox->SetSelectedForControl(true);
				// ゲームの操作モードをControlBoxモードに切り替える
				m_currentControlMode = GameControlMode::ControlBox;
			}
		}
	}

	// Boxの操作を終了し、SelectBoxモードへ戻る関数
	void GameStage::ReleaseControlOfBox()
	{
		// 現在がControlBoxモードの場合のみ処理を行う
		if (m_currentControlMode == GameControlMode::ControlBox) 
		{
			// もし現在操作中のBoxがあれば、そのBoxに「操作対象でなくなった」ことを通知する
			if (m_currentlyControlledBox) 
			{
				m_currentlyControlledBox->SetSelectedForControl(false);
				m_currentlyControlledBox = nullptr; // 操作対象のポインタをクリア
			}
		}
		// ゲームの操作モードをSelectBoxモードに戻す
		m_currentControlMode = GameControlMode::SelectBox;
	}

	// テクスチャの読込
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

	}


	void GameStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);

	}

	void GameStage::OnUpdate2()
	{
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

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
					if (dynamic_pointer_cast<PauseManager>(obj))
					{
						obj->SetUpdateActive(true);
					}
				    if (dynamic_pointer_cast<Box>(obj))
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
