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
			Setting = AddGameObject<SoundSprite>(352.0f,0,1592.0f,1080.0f);
			Setting->SetTexture(L"TEX_Setting");
			Setting->SetPosition(0, 0, 0);
			//Setting->SetScale(2.5f, 2.5f, 0);

			//BGM
			auto BGM = AddGameObject<SoundSprite>(300.0f,0,200.0f,376.0f);
			BGM->SetTexture(L"TEX_Sound");
			BGM->SetPosition(-250, 50.0f, 0);
			m_soundSprites.push_back(BGM);//m_soundSpritesにBGMを入れる

			//soundVol
			auto soundVol = AddGameObject<SoundSprite>(750.0f,0,1150.0f,60.0f);
			soundVol->SetTexture(L"TEX_SoundVol");
			soundVol->SetPosition(0, 50.0f, 0);
			m_soundSprites.push_back(soundVol);

			//無音
			auto notSound = AddGameObject<SoundSprite>(0,200.0f,300.0f,400.0f);
			notSound->SetTexture(L"TEX_Sound");
			notSound->SetPosition(-0, 50.0f, 0);
			//notSound->SetScale(0.4f, 0.4f, 0.4f);
			notSound->SetDrawActive(true);
			m_soundSprites.push_back(notSound);

			//小音
			auto littleSound = AddGameObject<SoundSprite>(0,400.0f,300.0f,600.0f);
			littleSound->SetTexture(L"TEX_Sound");
			littleSound->SetPosition(-120, 50.0f, 0);
			//littleSound->SetScale(0.4f, 0.4f, 0.4f);
			littleSound->SetDrawActive(false);
			m_soundSprites.push_back(littleSound);

			//中音
			auto normalSound = AddGameObject<SoundSprite>(0,600.0f,300.0f,800.0f);
			normalSound->SetTexture(L"TEX_Sound");
			normalSound->SetPosition(-120, 50.0f, 0);
			//normalSound->SetScale(0.4f, 0.4f, 0.4f);
			normalSound->SetDrawActive(false);
			m_soundSprites.push_back(normalSound);

			//大音
			auto bigSound = AddGameObject<SoundSprite>(0,800.0f,300.0f,1000.0f);
			bigSound->SetTexture(L"TEX_Sound");
			bigSound->SetPosition(-120, 50.0f, 0);
			//bigSound->SetScale(0.4f, 0.4f, 0.4f);
			bigSound->SetDrawActive(false);
			m_soundSprites.push_back(bigSound);

			//ブロック
			auto soundVolBox = AddGameObject<SoundSprite>(0,0,200.0f,200.0f);
			soundVolBox->SetTexture(L"TEX_Sound");
			soundVolBox->SetPosition(m_volumeLevel, 50.0f, 0);//-40.0f~240.0fなので１ブロック46.4くらい
			//soundVolBox->SetScale(1.5f, 1.5f, 1.5f);
			soundVolBox->SetDrawActive(true);
			m_soundSprites.push_back(soundVolBox);

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

			//右に傾けた時
			if (CntlVec[0].fThumbLX >= 0.8f)
			{
				m_volume += 0.2f;
				m_volumeLevel += 46.4f;
				if (m_volume > 1.0f)
				{
					m_volume = 1.0f;
					m_volumeLevel = 240.0f;
				}
			}
			//左に傾けた時
			if (CntlVec[0].fThumbLX <= -0.8f)
			{
				m_volume -= 0.2f;
				m_volumeLevel -= 46.4f;
				if (m_volume < 0.0f)
				{
					m_volume = 0.0f;
					m_volumeLevel = -200.0f;
				}
			}
			m_BGM->m_SourceVoice->SetVolume(m_volume);

			auto BGM = m_soundSprites[6].lock();
			BGM->SetPosition(m_volumeLevel, 50.0f, 0.0f);


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
		app->RegisterTexture(L"TEX_Sound", texPath + L"Sound.png");

	}

	void SettingStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}



}
//end basecross
