	/*!
@file Character.cpp
@brief キタイトルステージの実体
*/

#include "stdafx.h"
#include "Project.h"
#pragma once

	namespace basecross {

		//--------------------------------------------------------------------------------------
		//	ゲームステージクラス実体
		//--------------------------------------------------------------------------------------

		//ビューとライトの作成
		void StageSelect::CreateViewLight() {
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

		void StageSelect::OnCreate() {
			try {

				//ビューとライトの作成
				CreateViewLight();

				//テクスチャの読込
				//LoadTextures();

				//auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, 0.1f);

			}
			catch (...) {
				throw;
			}

		}


		void StageSelect::OnUpdate()
		{
			//コントローラチェックして入力があればコマンド呼び出し
			m_InputHandler.PushHandle(GetThis<StageSelect>());
		}

		////コントローラーのAボタンでゲーム画面に移動
		//void StageSelect::OnPushA()
		//{
		//	auto scene = App::GetApp()->GetScene<Scene>();
		//	PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToGameStage");

		//	//一定時間後にスプライトを削除する（タイトル画面からゲームステージに移るタイミング）
		//	PostEvent(5.0f, GetThis<ObjectInterface>(), scene, L"RemoveSprite");
		//}

		void SelectMassege::OnCreate() {
			ChangeWindowMode(true);
			if (DxLib_Init() == -1) return;
			SetFontSize(30);
			currentScene = Scene::Start;  // 初期シーンの設定
		}

		void SelectMassege::OnUpdate() {
			switch (currentScene) {
			case Scene::Start:
				currentScene = StartScene();
				break;
			case Scene::Init:
				currentScene = GameInit();
				break;
			case Scene::Game:
				currentScene = GameScene();
				break;
			case Scene::End:
				break;
			}
		}
		int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
		{
			SelectMassege selectMassege;
			selectMassege.OnCreate(); // 初期化処理を実行

			while (ProcessMessage() == 0 && selectMassege.isRunning()) {
				selectMassege.OnUpdate(); // シーン更新処理
				selectMassege.drawScene(); // 描画処理
			}

			DxLib_End();
			return 0;
		}
		//void StageSelect::OnDestroy() {
		//	//BGMのストップ
		//	auto XAPtr = App::GetApp()->GetXAudio2Manager();
		//	XAPtr->Stop(m_BGM);
		//}

	}
	//end basecross
