/*!
@file Character.cpp
@brief 操作説明の実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void Opelation::CreateViewLight() {
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

	void Opelation::OnCreate() {
		try {

			//ビューとライトの作成
			CreateViewLight();

			//テクスチャの読込
			LoadTextures();

			//タイトルスプライトの表示
			AddGameObject<OpelationSprite>();


			auto scene = App::GetApp()->GetScene<Scene>();
			auto volumeBGM = scene->m_volumeBGM;

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, volumeBGM);


			m_once = false;

		}
		catch (...) {
			throw;
		}

	}


	void Opelation::OnUpdate()
	{
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Opelation>());


		auto delta = App::GetApp()->GetElapsedTime();
		m_totalTime += delta;

	}

	//コントローラーのAボタンでゲーム画面に移動
	void Opelation::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto volumeSE = scene->m_volumeSE;
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		m_SE = ptrXA->Start(L"button_SE", 0, volumeSE);

		if (m_once == false)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToSelectStage");

			m_once = true;
		}
	}

	void Opelation::LoadTextures()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// メディアフォルダの取得
		auto mediaPath = app->GetDataDirWString();

		// テクスチャフォルダの定義
		auto texPath = mediaPath + L"Textures\\";

		// テクスチャの読込と登録
		app->RegisterTexture(L"TEX_OPELATION", texPath + L"Sousasetumei.png");

	}

	void Opelation::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

}
//end basecross
