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


			//スプライトオブジェクトの追加
			Setting = AddGameObject<SoundSprite>();
			Setting->SetTexture(L"TEX_Setting");
			Setting->SetPosition(0, 0, 0);
			Setting->SetScale(2.5f, 2.5f, 0);

			//BGM
			auto BGM = AddGameObject<SoundSprite>();
			BGM->SetTexture(L"TEX_BGM");
			BGM->SetPosition(-250, 50.0f, 0);
			m_soundSprites.push_back(BGM);//m_soundSpritesにBGMを入れる

			//soundVol
			auto soundVol = AddGameObject<SoundSprite>();
			soundVol->SetTexture(L"TEX_SoundVol");
			soundVol->SetPosition(100, 50.0f, 0);
			m_soundSprites.push_back(soundVol);

			//無音
			auto notSound = AddGameObject<SoundSprite>();
			notSound->SetTexture(L"TEX_NotSound");
			notSound->SetPosition(-120, 50.0f, 0);
			notSound->SetScale(0.4f, 0.4f, 0.4f);
			notSound->SetDrawActive(true);
			m_soundSprites.push_back(notSound);
			
			//小音
			auto littleSound = AddGameObject<SoundSprite>();
			littleSound->SetTexture(L"TEX_LittleSound");
			littleSound->SetPosition(-120, 50.0f, 0);
			littleSound->SetScale(0.4f, 0.4f, 0.4f);
			littleSound->SetDrawActive(false);
			m_soundSprites.push_back(littleSound);

			//中音
			auto normalSound = AddGameObject<SoundSprite>();
			normalSound->SetTexture(L"TEX_NormalSound");
			normalSound->SetPosition(-120, 50.0f, 0);
			normalSound->SetScale(0.4f, 0.4f, 0.4f);
			normalSound->SetDrawActive(false);
			m_soundSprites.push_back(normalSound);

			//大音
			auto bigSound = AddGameObject<SoundSprite>();
			bigSound->SetTexture(L"TEX_BigSound");
			bigSound->SetPosition(-120, 50.0f, 0);
			bigSound->SetScale(0.4f, 0.4f, 0.4f);
			bigSound->SetDrawActive(false);
			m_soundSprites.push_back(bigSound);

			for (int i = 0; i < 5; i++)
			{
				auto soundVolBox = AddGameObject<SoundSprite>();
				soundVolBox->SetTexture(L"TEX_SoundVolBox");
				soundVolBox->SetPosition(-40.0f, 50.0f, 0);//-40.0f~240.0fなので１ブロック46.4くらい
				soundVolBox->SetScale(1.5f, 1.5f, 1.5f);
				soundVolBox->SetDrawActive(true);
				m_soundVolBoxSprites.push_back(soundVolBox);
			}
			//BGM
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, m_volume);

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

		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//ゲームステージへ
			//Aボタンを押したときにゲームステージに移動する
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				PostEvent(0.0f, GetThis<SettingStage>(), scene, L"ToGameStage");
				return;
			}

			//左スティックのx軸
			float stickX = CntlVec[0].fThumbLX;
			bool rightMove = (stickX >= 0.8f);//右に傾けたか
			bool leftMove = (stickX <= -0.8f);//左に傾けたか

			if (rightMove && m_volumeLevel < 5)
			{
				m_volumeLevel++;
			}
			else if (leftMove && m_volumeLevel > 0)
			{
				m_volumeLevel--;
			}

			// 音量を6段階に設定 (0.0 ~ 1.0 の範囲)
			m_volume = m_volumeLevel / 5.0f;

			// BGMの音量変更
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, m_volume);

			// `soundVolBox` の表示個数を変更
			for (size_t i = 0; i < m_soundVolBoxSprites.size(); i++)
			{
				auto spritePtr = m_soundVolBoxSprites[i].lock();
				if (spritePtr)
				{
					spritePtr->SetDrawActive(i < m_volumeLevel);
				}
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
		app->RegisterTexture(L"TEX_LittleSound", texPath + L"LittleSound.png");
		app->RegisterTexture(L"TEX_NormalSound", texPath + L"NormalSound.png");
		app->RegisterTexture(L"TEX_BigSound", texPath + L"BigSound.png");
		app->RegisterTexture(L"TEX_NotSound", texPath + L"NotSound.png");

	}

	void SettingStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}



}
//end basecross
