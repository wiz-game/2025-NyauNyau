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
		void SelectStage::CreateViewLight() {
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

		void SelectStage::OnCreate() {
			try {

				//�r���[�ƃ��C�g�̍쐬
				CreateViewLight();

				//�e�N�X�`���̓Ǎ�
				LoadTextures();

				//�X�v���C�g�I�u�W�F�N�g�̒ǉ�
				//�X�e�[�W�P
				auto stage1 = AddGameObject<SelectStageSprite>(
					true, Vec2(256.0f, 64.0f), Vec2(0.0f, 100.0f));
				stage1->SetTexture(L"TEX_STAGE1");
				m_stageSprites.push_back(stage1);

				//�X�^�[�W�Q
				auto stage2 = AddGameObject<SelectStageSprite>(
					true, Vec2(256.0f, 64.0f), Vec2(0.0f, 0.0f));
				stage1->SetTexture(L"TEX_STAGE2");
				m_stageSprites.push_back(stage2);

				//�X�e�[�W�R
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
			//�V�[���̎擾
			auto PtrScene = App::GetApp()->GetScene<Scene>();
			int StageNum = PtrScene->GetStageNum();

			

			//�R���g���[���̎擾
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (CntlVec[0].bConnected)
			{
				//�Q�[���X�e�[�W��
				//A�{�^�����������Ƃ��ɃQ�[���X�e�[�W�Ɉړ�����
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{
					PostEvent(0.0f, GetThis<SelectStage>(), PtrScene, L"ToGameStage");
					return;
				}

				//CntrolLock = false�̎�
				if (!m_CntrolLock)
				{
					//�����
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
					//������
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

					//�X�v���C�g�̓_�ł����Z�b�g
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
			// �A�v���P�[�V�����I�u�W�F�N�g���擾����
			auto& app = App::GetApp();

			// ���f�B�A�t�H���_�̎擾
			auto mediaPath = app->GetDataDirWString();

			// �e�N�X�`���t�H���_�̒�`
			auto texPath = mediaPath + L"Textures\\";

			// �e�N�X�`���̓Ǎ��Ɠo�^
			app->RegisterTexture(L"TEX_STAGE1", texPath + L"stage1.png");
			app->RegisterTexture(L"TEX_STAGE2", texPath + L"stage2.png");
			app->RegisterTexture(L"TEX_STAGE3", texPath + L"stage3.png");
		}

	}
	//end basecross
