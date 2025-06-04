/*!
@file Character.cpp
@brief ゴールタイトルステージの実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゴールステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void goalStage::CreateViewLight() {
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

	void goalStage::OnCreate() {
		try {

			//ビューとライトの作成
			CreateViewLight();

			//テクスチャの読込
			LoadTextures();

			//スプライトオブジェクト
			AddGameObject<gameClearSprite>();
			AddGameObject<BackTitleButton>();

			auto scene = App::GetApp()->GetScene<Scene>();
			auto volume = scene->m_volume;

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"GameClearbgm", XAUDIO2_LOOP_INFINITE, volume);


		}

		catch (...) {
			throw;
		}

	}

	void goalStage::OnUpdate()
	{
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<goalStage>());

	}

	//コントローラーのAボタンでゲーム画面に移動
	void goalStage::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		PostEvent(1.3f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");
	}

	void goalStage::LoadTextures()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// メディアフォルダの取得
		auto mediaPath = app->GetDataDirWString();

		// テクスチャフォルダの定義
		auto texPath = mediaPath + L"Textures\\";

		// テクスチャの読込と登録
		app->RegisterTexture(L"TEX_GOALSTAGE", texPath + L"GoalStage.png");
		app->RegisterTexture(L"TEX_BACKTITLE", texPath + L"Back Title.png");
	}
	void goalStage::OnDestroy()
	{
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);


	}
}
//end basecross
