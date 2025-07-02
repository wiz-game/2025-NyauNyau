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
	void SettingStage::CreateViewLight() {
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

	void SettingStage::OnCreate() {
		try {

			//ビューとライトの作成
			CreateViewLight();

			//テクスチャの読込
			LoadTextures();

			auto scene = App::GetApp()->GetScene<Scene>();
			auto volumeBGM = scene->m_volumeBGM;
			auto volumeLevelBGM = scene->m_volumeLevelBGM;

			auto volumeSE = scene->m_volumeSE;
			auto volumeLevelSE = scene->m_volumeLevelSE;


			//スプライトオブジェクトの追加
			Setting = AddGameObject<SoundSprite>(/*352.0f,0,1592.0f,1080.0f*/);
			Setting->SetTexture(L"TEX_Setting");
			Setting->SetPosition(0, 0, 0);
			Setting->SetScale(2.5f, 2.5f, 0);

			//BGM
			auto BGM = AddGameObject<SoundSprite>(/*300.0f,0,200.0f,376.0f*/);
			BGM->SetTexture(L"TEX_BGM");
			BGM->SetPosition(0, 130.0f, 0);
			m_BGMsoundSprites.push_back(BGM);//m_soundSpritesにBGMを入れる

			//soundVol
			auto BGM_soundVol = AddGameObject<SoundSprite>(/*750.0f,0,1150.0f,60.0f*/);
			BGM_soundVol->SetTexture(L"TEX_SoundVol");
			BGM_soundVol->SetPosition(0, -78.0f, 0);
			m_BGMsoundSprites.push_back(BGM_soundVol);

			//ブロック
			auto BGM_soundVolBox = AddGameObject<SoundSprite>(/*0,0,200.0f,200.0f*/);
			BGM_soundVolBox->SetTexture(L"TEX_SoundVolBox");
			BGM_soundVolBox->SetPosition(volumeLevelBGM,-0.0f, 0);//-40.0f~240.0fなので１ブロック46.4くらい
			BGM_soundVolBox->SetScale(1.0f, 0.85f, 1.0f);
			BGM_soundVolBox->SetDrawActive(true);
			m_BGMsoundSprites.push_back(BGM_soundVolBox);




			//SE
			auto SE = AddGameObject<SoundSprite>(/*300.0f,0,200.0f,376.0f*/);
			SE->SetTexture(L"TEX_SE");
			SE->SetPosition(0, -90.0f, 0);
			m_SEsoundSprites.push_back(SE);//m_soundSpritesにBGMを入れる


			//soundVol
			auto SE_soundVol = AddGameObject<SoundSprite>(/*750.0f,0,1150.0f,60.0f*/);
			SE_soundVol->SetTexture(L"TEX_SoundVol");
			SE_soundVol->SetPosition(0, -290.0f, 0);
			m_SEsoundSprites.push_back(SE_soundVol);

			//ブロック
			auto SE_soundVolBox = AddGameObject<SoundSprite>(/*0,0,200.0f,200.0f*/);
			SE_soundVolBox->SetTexture(L"TEX_SoundVolBox");
			SE_soundVolBox->SetPosition(volumeLevelSE, -163.0f, 0);//-40.0f~240.0fなので１ブロック46.4くらい
			SE_soundVolBox->SetScale(1.0f, 0.85f, 1.0f);
			SE_soundVolBox->SetDrawActive(true);
			m_SEsoundSprites.push_back(SE_soundVolBox);


			//UI
			m_StageUI = AddGameObject<GameStageUI>();
			auto stageUI = m_StageUI.lock();
			stageUI->SetTexture(L"TEX_StageUI");
			stageUI->SetPosition(380.0f, -300.0f, 0);
			stageUI->SetScale(0.5f, 0.7f, 0);


			//BGM
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Gamebgm", XAUDIO2_LOOP_INFINITE, volumeBGM);

		}
		catch (...) {
			throw;
		}

	}


	void SettingStage::OnUpdate()
	{
		//経過時間を取得
		auto delta = App::GetApp()->GetElapsedTime();
		//sceneを取得	
		auto scene = App::GetApp()->GetScene<Scene>();

		//SEのテスト再生用タイマー
		static float seCooldown = 0.0f;
		if (seCooldown > 0.0f)
		{
			seCooldown -= delta;
		}

		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//ゲームステージへ
			//Aボタンを押したときにゲームステージに移動する
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				m_SE = ptrXA->Start(L"button_SE", 0, scene->m_volumeSE);

				PostEvent(0.0f, GetThis<SettingStage>(), scene, L"ToGameStage");
				return;
			}

			if (!m_MenuNavigationLock)
			{
				if (CntlVec[0].fThumbLY >= 0.8f)
				{
					isBGMSelected = true;
					m_MenuNavigationLock = true;
				}
				else if (CntlVec[0].fThumbLY <= -0.8f)
				{
					isBGMSelected = false;
					m_MenuNavigationLock = true;
				}
			}
			else
			{
				if (CntlVec[0].fThumbLY > -0.5f && CntlVec[0].fThumbLY < 0.5f)
				{
					m_MenuNavigationLock = false;
				}
			}

			if (isBGMSelected)
			{
				//BGM
				//右に傾けた時
				if (CntlVec[0].fThumbLX >= 0.8f)
				{
					scene->m_volumeBGM += 0.01f;
					scene->m_volumeLevelBGM += 5.4f;
					volumeChanged = true;
					if (scene->m_volumeBGM > 1.0f && scene->m_volumeLevelBGM > 270.0f)
					{
						scene->m_volumeBGM = 1.0f;
						scene->m_volumeLevelBGM = 270.0f;
					}
				}
				//左に傾けた時
				if (CntlVec[0].fThumbLX <= -0.8f)
				{
					scene->m_volumeBGM -= 0.01f;
					scene->m_volumeLevelBGM -= 5.4f;
					volumeChanged = true;
					if (scene->m_volumeBGM < 0.0f && scene->m_volumeLevelBGM < -270.0f)
					{
						scene->m_volumeBGM = 0.0f;
						scene->m_volumeLevelBGM = -270.0f;
					}
				}
				m_BGM->m_SourceVoice->SetVolume(scene->m_volumeBGM);

				auto BGM = m_BGMsoundSprites[2].lock();
				BGM->SetPosition(scene->m_volumeLevelBGM, 50.0f, 0.0f);
			}

			else
			{
				//SE
				//右に傾けた時
				if (CntlVec[0].fThumbLX >= 0.8f)
				{
					scene->m_volumeSE += 0.01f;
					scene->m_volumeLevelSE += 5.4f;
					volumeChanged = true;
					if (scene->m_volumeSE > 1.0f && scene->m_volumeLevelSE > 270.0f)
					{
						scene->m_volumeSE = 1.0f;
						scene->m_volumeLevelSE = 270.0f;
					}
				}
				//左に傾けた時
				if (CntlVec[0].fThumbLX <= -0.8f)
				{
					scene->m_volumeSE -= 0.01f;
					scene->m_volumeLevelSE -= 5.4f;
					volumeChanged = true;
					if (scene->m_volumeSE < 0.0f && scene->m_volumeLevelSE < -270.0f)
					{
						scene->m_volumeSE = 0.0f;
						scene->m_volumeLevelSE = -270.0f;
					}
				}

				//音量が変更され、かつクールダウンが終わっていたらテストSEを再生
				if (volumeChanged && seCooldown <= 0.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(L"button_SE", 0, scene->m_volumeSE);
					seCooldown = 1.0f;//0.2秒のクールダウン
				}
				//m_SE->m_SourceVoice->SetVolume(scene->m_volumeSE);

				auto SE = m_SEsoundSprites[2].lock();
				SE->SetPosition(scene->m_volumeLevelSE, -163.0f, 0.0f);
			}
		}
	}


	void SettingStage::LoadTextures()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// メディアフォルダの取得
		auto mediaPath = app->GetDataDirWString();

		// テクスチャフォルダの定義
		auto texPath = mediaPath + L"Textures\\";

		// テクスチャの読込と登録
		app->RegisterTexture(L"TEX_Setting", texPath + L"Setting.png");
		app->RegisterTexture(L"TEX_BGM", texPath + L"BGM.png");
		app->RegisterTexture(L"TEX_SE", texPath + L"SE.png");
		app->RegisterTexture(L"TEX_SoundVol", texPath + L"SoundVol.png");
		app->RegisterTexture(L"TEX_SoundVolBox", texPath + L"SoundVolBox.png");
		//app->RegisterTexture(L"TEX_Sound", texPath + L"Sound.png");
		app->RegisterTexture(L"TEX_StageUI", texPath + L"SettingStageUI.png");


	}

	void SettingStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}



}
//end basecross
