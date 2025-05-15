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
				//ステージ１
				auto stage1 = AddGameObject<SelectStageSprite>(
					true, Vec2(256.0f, 64.0f), Vec2(0.0f, 100.0f));
				stage1->SetTexture(L"TEX_STAGE1");
				m_stageSprites.push_back(stage1);

				//スタージ２
				auto stage2 = AddGameObject<SelectStageSprite>(
					true, Vec2(256.0f, 64.0f), Vec2(0.0f, 0.0f));
				stage1->SetTexture(L"TEX_STAGE2");
				m_stageSprites.push_back(stage2);

				//ステージ３
				auto stage3 = AddGameObject<SelectStageSprite>(
					true, Vec2(256.0f, 64.0f), Vec2(0.0f, -100.0f));
				stage1->SetTexture(L"TEX_STAGE3");
				m_stageSprites.push_back(stage3);

				//auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, 0.1f);

			}
			catch (...) {
				throw;
			}

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

					//スプライトの点滅をリセット
					for (int i = 0; i < 3; i++)
					{
						m_stageSprites[i]->SetSelected(false);
					}

					m_stageSprites[StageNum - 1]->SetSelected(true);

				}
				else
				{
					if (CntlVec[0].fThumbLY == 0.0f)
					{
						m_CntrolLock = false;
					}
				}
			}
		}

		void SelectStage::ChangeSelect(int num) 
		{
			for (int i = 0; i < 3; i++)
			{
				std::shared_ptr<SelectStageSprite> m_Srptr = m_stageSprites[i].lock();
				if (m_Srptr)
				{
					if ((i + 1) == num)
					{
						m_Srptr->SetSelected(true);
					}
					else
					{
						m_Srptr->SetSelected(false);
					}
				}

			}
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

	}
	//end basecross
