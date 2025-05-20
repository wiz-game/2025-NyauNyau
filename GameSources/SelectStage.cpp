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

				CreateFootprints();

				//�X�v���C�g�I�u�W�F�N�g�̒ǉ�
				//�X�e�[�W�P
				auto stage1 = AddGameObject<SelectStageSprite>();
				stage1->SetTexture(L"TEX_STAGE1");
				stage1->SetPosition(0, 200.0f, 0);
				stage1->SetSelected(true);
				m_stageSprites.push_back(stage1);//m_stageSprites��stage1������

				//�X�^�[�W�Q
				auto stage2 = AddGameObject<SelectStageSprite>();
				stage2->SetTexture(L"TEX_STAGE2");
				stage2->SetPosition(0, 0, 0);
				m_stageSprites.push_back(stage2);

				//�X�e�[�W�R
				auto stage3 = AddGameObject<SelectStageSprite>();
				stage3->SetTexture(L"TEX_STAGE3");
				stage3->SetPosition(0, -200.0f, 0);
				m_stageSprites.push_back(stage3);

				//���O�p���
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
						//�X�e�[�W�P����ɃX�e�B�b�N�𓮂�������X�e�[�W�R�Ɉړ�
						if (StageNum < 0)
						{
							StageNum = 2;
						}
						m_CntrolLock = true;
						PtrScene->SetStageNum(StageNum);
						ChangeSelect(StageNum);
						SetSelectYPosition(StageNum);
						//�|�C���g�X�v���C�g�̍��W�ύX

						if (leftPointSprite)
						{
							leftPointSprite->SetPosition(-250.0f, m_select, 0);
						}

					}
					//������
					else if (CntlVec[0].fThumbLY <= -0.8f)
					{
						StageNum++;
						//�X�e�[�W�R�ɗ�����X�e�[�W�P�ɖ߂�
						if (StageNum >= 3)
						{
							StageNum = 0;
						}
						m_CntrolLock = true;
						PtrScene->SetStageNum(StageNum);
						ChangeSelect(StageNum);
						SetSelectYPosition(StageNum);
						//�|�C���g�X�v���C�g�̍��W�ύX
						if (leftPointSprite)
						{
							leftPointSprite->SetPosition(-250.0f, m_select, 0);
						}
					}

				}
				//�������Ă��Ȃ���
				else
				{
					if (CntlVec[0].fThumbLY == 0.0f)
					{
						m_CntrolLock = false;
					}
				}
			}
			//�o�ߎ��Ԃ��擾
			auto delta = App::GetApp()->GetElapsedTime();

			static float timeElapsed = 0.0f;
			timeElapsed += delta;

			//�~�������悤�ȑ��Ձi�r���j
			const float centerX = 270.0f; // �O���̒��S
			const float centerY = -175.0f;
			const float radius = 200.0f; // ���a
			const float speed = XM_PI / 3.0f; // ���x�i�~����`�������j

			int index = static_cast<int>(timeElapsed / 0.5f);//0.5�b���Ƃɑ��Ղ�\������

			if (index < m_footprints.size())
			{
				auto footprintPtr = m_footprints[index].lock();
				if (footprintPtr)
				{
					footprintPtr->SetDrawActive(true);
					float angle = speed * index; // ���Ԃɉ������p�x
					float newX = centerX + radius * cos(angle);
					float newY = centerY + radius * sin(angle);
					footprintPtr->SetPosition(newX, newY, 0);
					footprintPtr->SetDrawActive(true);
				}
			}
		}

		//�I�����Ă���Sprite��_�ł����鏈��
		void SelectStage::ChangeSelect(int num) 
		{
			for (int i = 0; i < 3; i++)
			{
				std::shared_ptr<SelectStageSprite> srptr = m_stageSprites[i].lock();
				if (srptr)
				{
					//StageNum��m_stageSprites�ƈ�v���Ă�����
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

		//�X�e�[�W�ԍ�����m_select��ݒ肷��֐�
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

		//�l�R�̑��Ղ̏���
		void SelectStage::CreateFootprints()
		{
			const int footprintCount = 10;//�l�R�̑��Ղ̐�
			const float startX = -100.0f;//������
			const float startY = -350.0f;
			const float endX = 640.0f;//�����E
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
				footprint->SetDrawActive(false);//�ŏ��͔�\��
				m_footprints.push_back(footprint);
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
			app->RegisterTexture(L"TEX_POINT", texPath + L"point.png");
			app->RegisterTexture(L"TEX_POINT2", texPath + L"point2.png");
			app->RegisterTexture(L"TEX_FOOTPRINT", texPath + L"Footprint.png");

		}


	}
	//end basecross
