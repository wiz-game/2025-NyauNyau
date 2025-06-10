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
			auto volumeBGM = scene->m_volumeBGM;
			auto volumeLevelBGM = scene->m_volumeLevelBGM;

			auto volumeSE = scene->m_volumeSE;
			auto volumeLevelSE = scene->m_volumeLevelSE;


			//�X�v���C�g�I�u�W�F�N�g�̒ǉ�
			Setting = AddGameObject<SoundSprite>(/*352.0f,0,1592.0f,1080.0f*/);
			Setting->SetTexture(L"TEX_Setting");
			Setting->SetPosition(0, 0, 0);
			Setting->SetScale(2.5f, 2.5f, 0);

			//BGM
			auto BGM = AddGameObject<SoundSprite>(/*300.0f,0,200.0f,376.0f*/);
			BGM->SetTexture(L"TEX_BGM");
			BGM->SetPosition(0, 130.0f, 0);
			m_BGMsoundSprites.push_back(BGM);//m_soundSprites��BGM������

			//soundVol
			auto BGM_soundVol = AddGameObject<SoundSprite>(/*750.0f,0,1150.0f,60.0f*/);
			BGM_soundVol->SetTexture(L"TEX_SoundVol");
			BGM_soundVol->SetPosition(0, -78.0f, 0);
			m_BGMsoundSprites.push_back(BGM_soundVol);

			//����
			auto BGM_notSound = AddGameObject<SoundSprite>(/*0,200.0f,300.0f,400.0*/);
			BGM_notSound->SetTexture(L"TEX_NotSound");
			BGM_notSound->SetPosition(-370, 50.0f, 0);
			BGM_notSound->SetScale(0.4f, 0.4f, 0.4f);
			BGM_notSound->SetDrawActive(true);
			m_BGMsoundSprites.push_back(BGM_notSound);

			//����
			auto BGM_littleSound = AddGameObject<SoundSprite>(/*0,400.0f,300.0f,600.0f*/);
			BGM_littleSound->SetTexture(L"TEX_LittleSound");
			BGM_littleSound->SetPosition(-370, 50.0f, 0);
			BGM_littleSound->SetScale(0.4f, 0.4f, 0.4f);
			BGM_littleSound->SetDrawActive(false);
			m_BGMsoundSprites.push_back(BGM_littleSound);

			//����
			auto BGM_normalSound = AddGameObject<SoundSprite>(/*0,600.0f,300.0f,800.0f*/);
			BGM_normalSound->SetTexture(L"TEX_NormalSound");
			BGM_normalSound->SetPosition(-370, 50.0f, 0);
			BGM_normalSound->SetScale(0.4f, 0.4f, 0.4f);
			BGM_normalSound->SetDrawActive(false);
			m_BGMsoundSprites.push_back(BGM_normalSound);

			//�剹
			auto BGM_bigSound = AddGameObject<SoundSprite>(/*0,800.0f,300.0f,1000.0f*/);
			BGM_bigSound->SetTexture(L"TEX_BigSound");
			BGM_bigSound->SetPosition(-370, 50.0f, 0);
			BGM_bigSound->SetScale(0.4f, 0.4f, 0.4f);
			BGM_bigSound->SetDrawActive(false);
			m_BGMsoundSprites.push_back(BGM_bigSound);

			//�u���b�N
			auto BGM_soundVolBox = AddGameObject<SoundSprite>(/*0,0,200.0f,200.0f*/);
			BGM_soundVolBox->SetTexture(L"TEX_SoundVolBox");
			BGM_soundVolBox->SetPosition(volumeLevelBGM,-0.0f, 0);//-40.0f~240.0f�Ȃ̂łP�u���b�N46.4���炢
			BGM_soundVolBox->SetScale(1.0f, 0.85f, 1.0f);
			BGM_soundVolBox->SetDrawActive(true);
			m_BGMsoundSprites.push_back(BGM_soundVolBox);




			//SE
			auto SE = AddGameObject<SoundSprite>(/*300.0f,0,200.0f,376.0f*/);
			SE->SetTexture(L"TEX_SE");
			SE->SetPosition(0, -90.0f, 0);
			m_SEsoundSprites.push_back(SE);//m_soundSprites��BGM������


			//soundVol
			auto SE_soundVol = AddGameObject<SoundSprite>(/*750.0f,0,1150.0f,60.0f*/);
			SE_soundVol->SetTexture(L"TEX_SoundVol");
			SE_soundVol->SetPosition(0, -290.0f, 0);
			m_SEsoundSprites.push_back(SE_soundVol);

			//����
			auto SE_notSound = AddGameObject<SoundSprite>(/*0,200.0f,300.0f,400.0*/);
			SE_notSound->SetTexture(L"TEX_NotSound");
			SE_notSound->SetPosition(-370, -163.0f, 0);
			SE_notSound->SetScale(0.4f, 0.4f, 0.4f);
			SE_notSound->SetDrawActive(false);
			m_SEsoundSprites.push_back(SE_notSound);

			//����
			auto SE_littleSound = AddGameObject<SoundSprite>(/*0,400.0f,300.0f,600.0f*/);
			SE_littleSound->SetTexture(L"TEX_LittleSound");
			SE_littleSound->SetPosition(-370, -163.0f, 0);
			SE_littleSound->SetScale(0.4f, 0.4f, 0.4f);
			SE_littleSound->SetDrawActive(false);
			m_SEsoundSprites.push_back(SE_littleSound);

			//����
			auto SE_normalSound = AddGameObject<SoundSprite>(/*0,600.0f,300.0f,800.0f*/);
			SE_normalSound->SetTexture(L"TEX_NormalSound");
			SE_normalSound->SetPosition(-370, -163.0f, 0);
			SE_normalSound->SetScale(0.4f, 0.4f, 0.4f);
			SE_normalSound->SetDrawActive(true);
			m_SEsoundSprites.push_back(SE_normalSound);

			//�剹
			auto SE_bigSound = AddGameObject<SoundSprite>(/*0,800.0f,300.0f,1000.0f*/);
			SE_bigSound->SetTexture(L"TEX_BigSound");
			SE_bigSound->SetPosition(-370, -163.0f, 0);
			SE_bigSound->SetScale(0.4f, 0.4f, 0.4f);
			SE_bigSound->SetDrawActive(false);
			m_SEsoundSprites.push_back(SE_bigSound);

			//�u���b�N
			auto SE_soundVolBox = AddGameObject<SoundSprite>(/*0,0,200.0f,200.0f*/);
			SE_soundVolBox->SetTexture(L"TEX_SoundVolBox");
			SE_soundVolBox->SetPosition(volumeLevelSE, -163.0f, 0);//-40.0f~240.0f�Ȃ̂łP�u���b�N46.4���炢
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
		//�o�ߎ��Ԃ��擾
		auto delta = App::GetApp()->GetElapsedTime();
		//scene���擾	
		auto scene = App::GetApp()->GetScene<Scene>();

		//SE�̃e�X�g�Đ��p�^�C�}�[
		static float seCooldown = 0.0f;
		if (seCooldown > 0.0f)
		{
			seCooldown -= delta;
		}

		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{
			//�Q�[���X�e�[�W��
			//A�{�^�����������Ƃ��ɃQ�[���X�e�[�W�Ɉړ�����
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
				//�E�ɌX������
				if (CntlVec[0].fThumbLX >= 0.8f)
				{
					scene->m_volumeBGM += 0.01f;
					scene->m_volumeLevelBGM += 5.5f;
					volumeChanged = true;
					if (scene->m_volumeBGM > 1.0f && scene->m_volumeLevelBGM > 270.0f)
					{
						scene->m_volumeBGM = 1.0f;
						scene->m_volumeLevelBGM = 270.0f;
					}
				}
				//���ɌX������
				if (CntlVec[0].fThumbLX <= -0.8f)
				{
					scene->m_volumeBGM -= 0.01f;
					scene->m_volumeLevelBGM -= 5.5f;
					volumeChanged = true;
					if (scene->m_volumeBGM < 0.0f && scene->m_volumeLevelBGM < -270.0f)
					{
						scene->m_volumeBGM = 0.0f;
						scene->m_volumeLevelBGM = -270.0f;
					}
				}
				m_BGM->m_SourceVoice->SetVolume(scene->m_volumeBGM);

				auto BGM = m_BGMsoundSprites[6].lock();
				BGM->SetPosition(scene->m_volumeLevelBGM, 50.0f, 0.0f);


				if (scene->m_volumeBGM == 0.00f)
				{
					auto sound1 = m_BGMsoundSprites[2].lock();
					sound1->SetDrawActive(true);

					auto sound2 = m_BGMsoundSprites[3].lock();
					sound2->SetDrawActive(false);

					auto sound3 = m_BGMsoundSprites[4].lock();
					sound3->SetDrawActive(false);

					auto sound4 = m_BGMsoundSprites[5].lock();
					sound4->SetDrawActive(false);
				}
				if (0.01f < scene->m_volumeBGM > 0.30f)
				{
					auto sound1 = m_BGMsoundSprites[2].lock();
					sound1->SetDrawActive(false);

					auto sound2 = m_BGMsoundSprites[3].lock();
					sound2->SetDrawActive(true);

					auto sound3 = m_BGMsoundSprites[4].lock();
					sound3->SetDrawActive(false);

					auto sound4 = m_BGMsoundSprites[5].lock();
					sound4->SetDrawActive(false);
				}
				if (0.30f < scene->m_volumeBGM > 0.70f)
				{
					auto sound1 = m_BGMsoundSprites[2].lock();
					sound1->SetDrawActive(false);

					auto sound2 = m_BGMsoundSprites[3].lock();
					sound2->SetDrawActive(false);

					auto sound3 = m_BGMsoundSprites[4].lock();
					sound3->SetDrawActive(true);

					auto sound4 = m_BGMsoundSprites[5].lock();
					sound4->SetDrawActive(false);
				}
				if (0.70f < scene->m_volumeBGM >= 1.00f)
				{
					auto sound1 = m_BGMsoundSprites[2].lock();
					sound1->SetDrawActive(false);

					auto sound2 = m_BGMsoundSprites[3].lock();
					sound2->SetDrawActive(false);

					auto sound3 = m_BGMsoundSprites[4].lock();
					sound3->SetDrawActive(false);

					auto sound4 = m_BGMsoundSprites[5].lock();
					sound4->SetDrawActive(true);
				}
			}

			else
			{
				//SE
				//�E�ɌX������
				if (CntlVec[0].fThumbLX >= 0.8f)
				{
					scene->m_volumeSE += 0.01f;
					scene->m_volumeLevelSE += 5.5f;
					volumeChanged = true;
					if (scene->m_volumeSE > 1.0f && scene->m_volumeLevelSE > 270.0f)
					{
						scene->m_volumeSE = 1.0f;
						scene->m_volumeLevelSE = 270.0f;
					}
				}
				//���ɌX������
				if (CntlVec[0].fThumbLX <= -0.8f)
				{
					scene->m_volumeSE -= 0.01f;
					scene->m_volumeLevelSE -= 5.5f;
					volumeChanged = true;
					if (scene->m_volumeSE < 0.0f && scene->m_volumeLevelSE < -270.0f)
					{
						scene->m_volumeSE = 0.0f;
						scene->m_volumeLevelSE = -270.0f;
					}
				}

				//���ʂ��ύX����A���N�[���_�E�����I����Ă�����e�X�gSE���Đ�
				if (volumeChanged && seCooldown <= 0.0f)
				{
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					ptrXA->Start(L"button_SE", 0, scene->m_volumeSE);
					seCooldown = 1.0f;//0.2�b�̃N�[���_�E��
				}
				//m_SE->m_SourceVoice->SetVolume(scene->m_volumeSE);

				auto SE = m_SEsoundSprites[6].lock();
				SE->SetPosition(scene->m_volumeLevelSE, -163.0f, 0.0f);


				if (scene->m_volumeSE == 0.00f)
				{
					auto sound1 = m_SEsoundSprites[2].lock();
					sound1->SetDrawActive(true);

					auto sound2 = m_SEsoundSprites[3].lock();
					sound2->SetDrawActive(false);

					auto sound3 = m_SEsoundSprites[4].lock();
					sound3->SetDrawActive(false);

					auto sound4 = m_SEsoundSprites[5].lock();
					sound4->SetDrawActive(false);
				}
				if (0.01f < scene->m_volumeSE > 0.30f)
				{
					auto sound1 = m_SEsoundSprites[2].lock();
					sound1->SetDrawActive(false);

					auto sound2 = m_SEsoundSprites[3].lock();
					sound2->SetDrawActive(true);

					auto sound3 = m_SEsoundSprites[4].lock();
					sound3->SetDrawActive(false);

					auto sound4 = m_SEsoundSprites[5].lock();
					sound4->SetDrawActive(false);
				}
				if (0.30f < scene->m_volumeSE > 0.70f)
				{
					auto sound1 = m_SEsoundSprites[2].lock();
					sound1->SetDrawActive(false);

					auto sound2 = m_SEsoundSprites[3].lock();
					sound2->SetDrawActive(false);

					auto sound3 = m_SEsoundSprites[4].lock();
					sound3->SetDrawActive(true);

					auto sound4 = m_SEsoundSprites[5].lock();
					sound4->SetDrawActive(false);
				}
				if (0.70f < scene->m_volumeSE >= 1.00f)
				{
					auto sound1 = m_SEsoundSprites[2].lock();
					sound1->SetDrawActive(false);

					auto sound2 = m_SEsoundSprites[3].lock();
					sound2->SetDrawActive(false);

					auto sound3 = m_SEsoundSprites[4].lock();
					sound3->SetDrawActive(false);

					auto sound4 = m_SEsoundSprites[5].lock();
					sound4->SetDrawActive(true);

				}
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
		app->RegisterTexture(L"TEX_StageUI", texPath + L"SettingStageUI.png");


	}

	void SettingStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}



}
//end basecross
