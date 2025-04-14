
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
		vector<vector<Vec3>> vec = {
			{
				Vec3(10.0f, 10.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 4.0f, 5.0f)
			},
			{
				Vec3(15.0f, 10.0f, 1.0f),
				Vec3(0.0f, XM_PI / 2, 0.0f),
				Vec3(-5.3f, 4.0f, 2.0f)
			}
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
