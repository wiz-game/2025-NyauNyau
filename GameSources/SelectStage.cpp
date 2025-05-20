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

				CreateFootprints();

				//スプライトオブジェクトの追加
				//ステージ１
				auto stage1 = AddGameObject<SelectStageSprite>();
				stage1->SetTexture(L"TEX_STAGE1");
				stage1->SetPosition(0, 200.0f, 0);
				stage1->SetSelected(true);
				m_stageSprites.push_back(stage1);//m_stageSpritesにstage1を入れる

				//スタージ２
				auto stage2 = AddGameObject<SelectStageSprite>();
				stage2->SetTexture(L"TEX_STAGE2");
				stage2->SetPosition(0, 0, 0);
				m_stageSprites.push_back(stage2);

				//ステージ３
				auto stage3 = AddGameObject<SelectStageSprite>();
				stage3->SetTexture(L"TEX_STAGE3");
				stage3->SetPosition(0, -200.0f, 0);
				m_stageSprites.push_back(stage3);

				//左三角矢印
				leftPointSprite = AddGameObject<SelectStageSprite>();
				leftPointSprite->SetTexture(L"TEX_POINT");
				leftPointSprite->SetPosition(-250.0f, m_select + 200.0f, 0);
				leftPointSprite->SetScale(0.25f, 0.25f, 0.25f);

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
						//ステージ１より上にスティックを動かしたらステージ３に移動
						if (StageNum < 0)
						{
							StageNum = 2;
						}
						m_CntrolLock = true;
						PtrScene->SetStageNum(StageNum);
						ChangeSelect(StageNum);
						SetSelectYPosition(StageNum);
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
						PtrScene->SetStageNum(StageNum);
						ChangeSelect(StageNum);
						SetSelectYPosition(StageNum);
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
			//経過時間を取得
			auto delta = App::GetApp()->GetElapsedTime();

			static float timeElapsed = 0.0f;
			timeElapsed += delta;

			//円を書くような足跡（途中）
			const float centerX = 270.0f; // 軌道の中心
			const float centerY = -175.0f;
			const float radius = 200.0f; // 半径
			const float speed = XM_PI / 3.0f; // 速度（円周を描く速さ）

			int index = static_cast<int>(timeElapsed / 0.5f);//0.5秒ごとに足跡を表示する

			if (index < m_footprints.size())
			{
				auto footprintPtr = m_footprints[index].lock();
				if (footprintPtr)
				{
					footprintPtr->SetDrawActive(true);
					float angle = speed * index; // 時間に応じた角度
					float newX = centerX + radius * cos(angle);
					float newY = centerY + radius * sin(angle);
					footprintPtr->SetPosition(newX, newY, 0);
					footprintPtr->SetDrawActive(true);
				}
			}
		}

		//選択しているSpriteを点滅させる処理
		void SelectStage::ChangeSelect(int num) 
		{
			for (int i = 0; i < 3; i++)
			{
				std::shared_ptr<SelectStageSprite> srptr = m_stageSprites[i].lock();
				if (srptr)
				{
					//StageNumがm_stageSpritesと一致していたら
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

		//ステージ番号からm_selectを設定する関数
		void SelectStage::SetSelectYPosition(int StageNum)
		{
			switch (StageNum)
			{
			case 0:
				m_select = 200.0f;
				break;
			case 1:
				m_select = 0;
				break;
			case 2:
				m_select = -200.0f;
				break;
			default:
				break;
			}
		}

		//ネコの足跡の処理
		void SelectStage::CreateFootprints()
		{
			const int footprintCount = 10;//ネコの足跡の数
			const float startX = -100.0f;//中央下
			const float startY = -350.0f;
			const float endX = 640.0f;//中央右
			const float endY = 0.0f;
			const float stepX = (endX - startX) / footprintCount;
			const float stepY = (endY - startY) / footprintCount;

			for (int i = 0; i < footprintCount; i++)
			{
				auto footprint = AddGameObject<FootprintSprite>();
				footprint->SetTexture(L"TEX_FOOTPRINT");
				footprint->SetPosition(startX + (stepX * i), startY + (stepY * i), 0);
				footprint->SetScale(0.2f, 0.2f, 0.2f);
				footprint->SetRotate(0, 0,-(XM_PI / 6));
				footprint->SetDrawActive(false);//最初は非表示
				m_footprints.push_back(footprint);
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
			app->RegisterTexture(L"TEX_POINT", texPath + L"point.png");
			app->RegisterTexture(L"TEX_POINT2", texPath + L"point2.png");
			app->RegisterTexture(L"TEX_FOOTPRINT", texPath + L"Footprint.png");

		}


	}
	//end basecross
