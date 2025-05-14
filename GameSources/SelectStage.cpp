	/*!
@file Character.cpp
@brief ステージセレクト画面の実体
*/

#include "stdafx.h"
#include "Project.h"
#pragma once

	namespace basecross {

		//--------------------------------------------------------------------------------------
		//	ステージセレクトクラス実体
		//--------------------------------------------------------------------------------------

		//ビューとライトの作成
		void SelectStage::CreateViewLight() {
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

		void SelectStage::OnCreate() {
			try {

				//ビューとライトの作成
				CreateViewLight();

				//テクスチャの読込
				LoadTextures();

				//スプライトオブジェクトの追加
				AddGameObject<Stage1>();
				AddGameObject<Stage2>();
				AddGameObject<Stage3>();


				//auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, 0.1f);

			}
			catch (...) {
				throw;
			}

			//文字列をつける
			//auto ptrString = AddComponent<StringSprite>();
			//ptrString->SetText(L"");
			//ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));


		}


		void SelectStage::OnUpdate()
		{
			//シーンの取得
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			int StageNum = PtrScene->GetStageNum();

			//コントローラの取得
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected)
			{
				//ゲームステージへ
				//Aボタンを押したときにゲームステージに移動する
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{
					PostEvent(0.0f, GetThis<SelectStage>(), PtrScene, L"ToGameStage");
					return;
				}

				//CntrolLock = falseの時
				if (!m_CntrolLock)
				{
					//上向き
					if (CntlVec[0].fThumbLY >= 0.8f)
					{
						StageNum--;
						if (StageNum < 1)
						{
							StageNum = 3;
						}
						m_CntrolLock = true;
						PtrScene->SetStageNum(StageNum);
						ChangeSelect(StageNum);
					}
					//下向き
					else if (CntlVec[0].fThumbLY <= -0.8f)
					{
						StageNum++;
						if (StageNum > 3)
						{
							StageNum = 1;
						}
						m_CntrolLock = true;
						PtrScene->SetStageNum(StageNum);
						ChangeSelect(StageNum);
					}

					//if (StageNum == 1)
					//{
					//	m_Blinking = true;
					//}
					//else if (StageNum == 2)
					//{
					//	m_Blinking = true;
					//}
					//else if (StageNum == 3)
					//{
					//	m_Blinking = true;
					//}
					if (StageNum >= 1 && StageNum <= 3)
					{
						m_Blinking = true;
					}
				}
				else
				{
					if (CntlVec[0].fThumbLY == 0.0f)
					{
						m_CntrolLock = false;
					}

					m_Blinking = false;
				}
			}

			//DrawString();

		}

		void SelectStage::ChangeSelect(int StageNum) 
		{
		}


		void SelectStage::LoadTextures()
		{
			// アプリケーションオブジェクトを取得する
			auto& app = App::GetApp();

			// メディアフォルダの取得
			auto mediaPath = app->GetDataDirWString();

			// テクスチャフォルダの定義
			auto texPath = mediaPath + L"Textures\\";

			// テクスチャの読込と登録
			app->RegisterTexture(L"TEX_STAGE1", texPath + L"stage1.png");
			app->RegisterTexture(L"TEX_STAGE2", texPath + L"stage2.png");
			app->RegisterTexture(L"TEX_STAGE3", texPath + L"stage3.png");
		}


		//void SelectStage::DrawString()
		//{
		//		// シーンの取得
		//		auto PtrScene = App::GetApp()->GetScene<Scene>();
		//		int StageNum = PtrScene->GetStageNum();

		//		// ステージ番号を表示する文字列を作成
		//		wstring stageStr(L"現在選択中のステージ:\t");
		//		stageStr += L"Stage " + std::to_wstring(StageNum) + L"\n";

		//		// 文字列コンポーネントの取得
		//		auto ptrString = GetComponent<StringSprite>();
		//		ptrString->SetText(stageStr);
		//}
		//void SelectStage::OnDestroy() {
		//	//BGMのストップ
		//	auto XAPtr = App::GetApp()->GetXAudio2Manager();
		//	XAPtr->Stop(m_BGM);
		//}

	}
	//end basecross
