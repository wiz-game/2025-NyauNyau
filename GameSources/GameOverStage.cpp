/*!
@file Character.cpp
@brief ゲームオーバーステージの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームオーバーステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void GameOverStage::CreateViewLight() {
		// カメラの設定
		auto camera = ObjectFactory::Create<Camera>();
		camera->SetEye(Vec3(0.0f, 5.0f, -15.0f));
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定
	}

	void GameOverStage::OnCreate() {
		try {

			//ビューとライトの作成
			CreateViewLight();

			//テクスチャの読込
			LoadTextures();

			//スプライトオブジェクト
			auto Rat = AddGameObject<GameSprite>();
			Rat->SetTexture(L"TEX_Rat");
			Rat->SetPosition(0, 0, 0);
			Rat->SetScale(2.0f, 1.0f, 1.0f);
			m_sprites.push_back(Rat);

			m_sprites.push_back(AddGameObject<GameOverSprite>());
			m_sprites.push_back(AddGameObject<BackTitleButton>());


			m_catSprite = AddGameObject<CatWalkSprite>();
			auto walk = m_catSprite.lock();
			walk->SetDrawActive(false);

			m_loading = AddGameObject<GameSprite>();
			auto loading = m_loading.lock();
			loading->SetTexture(L"TEX_Loading");
			loading->SetPosition(270, -350, 0);
			loading->SetScale(1.0f, 0.5f, 1.0f);
			loading->SetDrawActive(false);

			m_rat = AddGameObject<GameSprite>();
			auto rat = m_rat.lock();
			rat->SetTexture(L"TEX_NEZUMI");
			rat->SetPosition(610.0f, -385.0f, 0);
			rat->SetScale(0.1f, 0.2f, 1.0f);
			rat->SetDrawActive(false);
			rat->SetMovementActive(false);


			auto scene = App::GetApp()->GetScene<Scene>();
			auto volumeBGM = scene->m_volumeBGM;
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, volumeBGM);

		}
		catch (...) {
			throw;
		}

	}


	void GameOverStage::OnUpdate()
	{
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<GameOverStage>());
	}

	//コントローラーのAボタンでゲーム画面に移動
	void GameOverStage::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto volumeSE = scene->m_volumeSE;
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		m_SE = ptrXA->Start(L"button_SE", 0, volumeSE);

		StartCatWalkAnimation();
		PostEvent(3.0f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");
	}

	void GameOverStage::LoadTextures()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// メディアフォルダの取得
		auto mediaPath = app->GetDataDirWString();

		// テクスチャフォルダの定義
		auto texPath = mediaPath + L"Textures\\";

		// テクスチャの読込と登録
		app->RegisterTexture(L"TEX_GAMEOVER", texPath + L"GameOver.png");
		app->RegisterTexture(L"TEX_BACKTITLE", texPath + L"Back Title.png");
		app->RegisterTexture(L"TEX_Rat", texPath + L"Rat GameOver.png");

	}

	void GameOverStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}


	void GameOverStage::StartCatWalkAnimation()
	{
		//スプライトの非表示
		for (auto sprite : m_sprites)
		{
			RemoveGameObject<GameObject>(sprite);
		}


		if (auto spr = m_catSprite.lock())
		{
			spr->SetDrawActive(true);
			spr->StartAnimation();
		}
		if (auto spr = m_loading.lock())
		{
			spr->SetDrawActive(true);
		}
		if (auto spr = m_rat.lock())
		{
			spr->SetDrawActive(true);
			spr->SetMovementActive(true);
		}
	}

}
//end basecross
