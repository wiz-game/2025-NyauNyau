/*!
@file Character.cpp
@brief �X�e�[�W�Z���N�g��ʂ̎���
*/

#include "stdafx.h"
#include "Project.h"
#pragma once

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�N���X����
	//--------------------------------------------------------------------------------------

	//�r���[�ƃ��C�g�̍쐬
	void SettingStage::CreateViewLight() {
		// �J�����̐ݒ�
		auto camera = ObjectFactory::Create<Camera>();
		camera->SetEye(Vec3(0.0f, 5.0f, -15.0f));
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// �r���[�ɃJ������ݒ�
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//�}���`���C�g�̍쐬
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //�f�t�H���g�̃��C�e�B���O���w��
	}

	void SettingStage::OnCreate() {
		try {

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//�e�N�X�`���̓Ǎ�
			LoadTextures();

			auto scene = App::GetApp()->GetScene<Scene>();
			auto volume = scene->m_volume;
			auto volumeLevel = scene->m_volumeLevel;

			//�X�v���C�g�I�u�W�F�N�g�̒ǉ�
			Setting = AddGameObject<SoundSprite>(/*352.0f,0,1592.0f,1080.0f*/);
			Setting->SetTexture(L"TEX_Setting");
			Setting->SetPosition(0, 0, 0);
			Setting->SetScale(2.5f, 2.5f, 0);

			//BGM
			auto BGM = AddGameObject<SoundSprite>(/*300.0f,0,200.0f,376.0f*/);
			BGM->SetTexture(L"TEX_BGM");
			BGM->SetPosition(0, 130.0f, 0);
			m_soundSprites.push_back(BGM);//m_soundSprites��BGM������

			//soundVol
			auto soundVol = AddGameObject<SoundSprite>(/*750.0f,0,1150.0f,60.0f*/);
			soundVol->SetTexture(L"TEX_SoundVol");
			soundVol->SetPosition(0, -78.0f, 0);
			m_soundSprites.push_back(soundVol);

			//����
			auto notSound = AddGameObject<SoundSprite>(/*0,200.0f,300.0f,400.0*/);
			notSound->SetTexture(L"TEX_NotSound");
			notSound->SetPosition(-370, 50.0f, 0);
			notSound->SetScale(0.4f, 0.4f, 0.4f);
			notSound->SetDrawActive(true);
			m_soundSprites.push_back(notSound);

			//����
			auto littleSound = AddGameObject<SoundSprite>(/*0,400.0f,300.0f,600.0f*/);
			littleSound->SetTexture(L"TEX_LittleSound");
			littleSound->SetPosition(-370, 50.0f, 0);
			littleSound->SetScale(0.4f, 0.4f, 0.4f);
			littleSound->SetDrawActive(false);
			m_soundSprites.push_back(littleSound);

			//����
			auto normalSound = AddGameObject<SoundSprite>(/*0,600.0f,300.0f,800.0f*/);
			normalSound->SetTexture(L"TEX_NormalSound");
			normalSound->SetPosition(-370, 50.0f, 0);
			normalSound->SetScale(0.4f, 0.4f, 0.4f);
			normalSound->SetDrawActive(false);
			m_soundSprites.push_back(normalSound);

			//�剹
			auto bigSound = AddGameObject<SoundSprite>(/*0,800.0f,300.0f,1000.0f*/);
			bigSound->SetTexture(L"TEX_BigSound");
			bigSound->SetPosition(-370, 50.0f, 0);
			bigSound->SetScale(0.4f, 0.4f, 0.4f);
			bigSound->SetDrawActive(false);
			m_soundSprites.push_back(bigSound);

			//�u���b�N
			auto soundVolBox = AddGameObject<SoundSprite>(/*0,0,200.0f,200.0f*/);
			soundVolBox->SetTexture(L"TEX_SoundVolBox");
			soundVolBox->SetPosition(volumeLevel,-0.0f, 0);//-40.0f~240.0f�Ȃ̂łP�u���b�N46.4���炢
			soundVolBox->SetScale(1.0f, 0.85f, 1.0f);
			soundVolBox->SetDrawActive(true);
			m_soundSprites.push_back(soundVolBox);

			//BGM
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Gamebgm", XAUDIO2_LOOP_INFINITE, volume);

		}
		catch (...) {
			throw;
		}

	}


	void SettingStage::OnUpdate()
	{
		//�o�ߎ��Ԃ��擾
		auto delta = App::GetApp()->GetElapsedTime();
		//scene���擾	
		auto scene = App::GetApp()->GetScene<Scene>();

		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//�Q�[���X�e�[�W��
			//A�{�^�����������Ƃ��ɃQ�[���X�e�[�W�Ɉړ�����
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				PostEvent(0.0f, GetThis<SettingStage>(), scene, L"ToGameStage");
				return;
			}

			//�E�ɌX������
			if (CntlVec[0].fThumbLX >= 0.8f)
			{
				scene->m_volume += 0.01f;
				scene->m_volumeLevel += 5.5f;
				if (scene->m_volume > 1.0f)
				{
					scene->m_volume = 1.0f;
					scene->m_volumeLevel = 270.0f;
				}
			}
			//���ɌX������
			if (CntlVec[0].fThumbLX <= -0.8f)
			{
				scene->m_volume -= 0.01f;
				scene->m_volumeLevel -= 5.5f;
				if (scene->m_volume < 0.0f)
				{
					scene->m_volume = 0.0f;
					scene->m_volumeLevel = -270.0f;
				}
			}
			m_BGM->m_SourceVoice->SetVolume(scene->m_volume);

			auto BGM = m_soundSprites[6].lock();
			BGM->SetPosition(scene->m_volumeLevel, 50.0f, 0.0f);


			if (scene->m_volume == 0.00f)
			{
				auto sound1 = m_soundSprites[2].lock();
				sound1->SetDrawActive(true);

				auto sound2 = m_soundSprites[3].lock();
				sound2->SetDrawActive(false);

				auto sound3 = m_soundSprites[4].lock();
				sound3->SetDrawActive(false);

				auto sound4 = m_soundSprites[5].lock();
				sound4->SetDrawActive(false);
			}
			if (0.01f < scene->m_volume > 0.30f)
			{
				auto sound1 = m_soundSprites[2].lock();
				sound1->SetDrawActive(false);

				auto sound2 = m_soundSprites[3].lock();
				sound2->SetDrawActive(true);

				auto sound3 = m_soundSprites[4].lock();
				sound3->SetDrawActive(false);

				auto sound4 = m_soundSprites[5].lock();
				sound4->SetDrawActive(false);
			}
			if (0.30f < scene->m_volume > 0.70f)
			{
				auto sound1 = m_soundSprites[2].lock();
				sound1->SetDrawActive(false);

				auto sound2 = m_soundSprites[3].lock();
				sound2->SetDrawActive(false);

				auto sound3 = m_soundSprites[4].lock();
				sound3->SetDrawActive(true);

				auto sound4 = m_soundSprites[5].lock();
				sound4->SetDrawActive(false);
			}
			if (0.70f < scene->m_volume >= 1.00f)
			{
				auto sound1 = m_soundSprites[2].lock();
				sound1->SetDrawActive(false);

				auto sound2 = m_soundSprites[3].lock();
				sound2->SetDrawActive(false);

				auto sound3 = m_soundSprites[4].lock();
				sound3->SetDrawActive(false);

				auto sound4 = m_soundSprites[5].lock();
				sound4->SetDrawActive(true);

			}


		}

	}


	void SettingStage::LoadTextures()
	{
		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();

		// ���f�B�A�t�H���_�̎擾
		auto mediaPath = app->GetDataDirWString();

		// �e�N�X�`���t�H���_�̒�`
		auto texPath = mediaPath + L"Textures\\";

		// �e�N�X�`���̓Ǎ��Ɠo�^
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
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}



}
//end basecross
