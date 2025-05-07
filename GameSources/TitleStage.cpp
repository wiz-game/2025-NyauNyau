/*!
@file Character.cpp
@brief キタイトルステージの実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void TitleStage::CreateViewLight() {
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

	void TitleStage::OnCreate() {
		try {

			//ビューとライトの作成
			CreateViewLight();

			//テクスチャの読込
			LoadTextures();

			//スプライトオブジェクト
			AddGameObject<TitleSprite>();



			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, 0.1f);


			//MessageBox(0, L"ニャウニャウシルエット", L"タイトル", 0);
		}
		catch (...) {
			throw;
		}

	}


	void TitleStage::OnUpdate()
	{
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<TitleStage>());
	}

	//コントローラーのAボタンでゲーム画面に移動
	void TitleStage::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToGameStage");

		//一定時間後にスプライトを削除する（タイトル画面からゲームステージに移るタイミング）
		PostEvent(5.0f, GetThis<ObjectInterface>(), scene, L"RemoveSprite");
	}

	void TitleStage::LoadTextures()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// メディアフォルダの取得
		auto mediaPath = app->GetDataDirWString();

		// テクスチャフォルダの定義
		auto texPath = mediaPath + L"Textures\\";

		// テクスチャの読込と登録
		app->RegisterTexture(L"TEX_TITLESTAGE", texPath + L"TitleStage.png");
	}

	void TitleStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

}
//end basecross
