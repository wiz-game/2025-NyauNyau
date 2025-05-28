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

				//�l�R���
				catPointSprite = AddGameObject<SelectStageSprite>();
				catPointSprite->SetTexture(L"TEX_POINT");
				catPointSprite->SetPosition(-230.0f, m_select + 200.0f, 0);
				catPointSprite->SetScale(0.5f, 0.5f, 0.5f);

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
					PostEvent(0.0f, GetThis<SelectStage>(), PtrScene, L"ToSettingStage");
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

						if (catPointSprite)
						{
							catPointSprite->SetPosition(-250.0f, m_select, 0);
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
						if (catPointSprite)
						{
							catPointSprite->SetPosition(-250.0f, m_select, 0);
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

			const float frequency = XM_PI / 2.0f;//�g�̎���

			int index = static_cast<int>(timeElapsed / 0.3f); // 0.3�b���Ƃɑ��Ղ�\��

			if (index < m_footprints.size())
			{
				float waveValue = cos(frequency * index);//sin�g�̒l���v�Z

				//sin�g�̒l���P�܂���-�P�ɋ߂��ꍇ�ɕ\��
				if (waveValue > 0.99f || waveValue < -0.99f)
				{
					auto footprintPtr = m_footprints[index].lock();
					if (footprintPtr)
					{
						footprintPtr->SetDrawActive(true); // ���Ղ�\��

						static float moveDuration = 3.0f;
						static float moveElapsed = 0.0f;

						if (moveElapsed < moveDuration)
						{
							//�����畂���オ���Ă��鉉�o����
							moveElapsed += delta;
							//Vec3����float�ւ̕ϊ�
							Vec3 trans = footprintPtr->GetComponent<Transform>()->GetPosition();
							float startY = trans.y;//Y���W�̂ݎ��o��
							float targetY = startY + 0.3f;//�ڕW�̈ʒu

							float setY = startY + (targetY - startY) * (moveElapsed / moveDuration);
							
							//�t�F�[�h�C������
							float alpha = moveElapsed / moveDuration;//�����x�̌v�Z�i0.0~1.0�j
							footprintPtr->SetAlphaActive(alpha);//�A���t�@�l���X�V
							
							
							//footprintPtr->SetPosition(trans.x, setY, 0);
						}
					}
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
			const int footprintCount = 20; // �l�R�̑��Ղ̐�
			const float startX = -320.0f;  // ����X���W
			const float startY = -200.0f;  // ����Y���W
			const float endX = 320.0f;
			const float endY = 200.0f;
			//const float amplitude = 80.0f; // Sin�g�̐U���i�㉺�̕��j
			//const float frequency = XM_PI / 2.0f; // �g�̎����i�Ԋu�j

			Vec3 startPos(startX, startY, 0.0f);//�����ʒu
			Vec3 endPos(endX, endY, 0.0f);
			Vec3 stepPos = endPos - startPos;//�i�i���̈ړ�
			float naname = stepPos.length();
			float stepLen = naname / footprintCount;
			Vec3 v = stepPos.normalize();
			Vec3 z(0, 0, -1);
			
			Vec3 cross = v.cross(z);//�O��
			cross = cross.normalize();

			for (int i = 0; i < footprintCount; i++)
			{
				Vec3 pos(startPos + v * stepLen * i);

				if (i % 2 == 0)
				{
					pos += cross * 200.0f;

				}
				else
				{
					pos -= cross * 200.0f;

				}

				auto footprint = AddGameObject<FootprintSprite>();
				footprint->SetTexture(L"TEX_FOOTPRINT");
				footprint->SetPosition(pos.x, pos.y, 0);
				footprint->SetScale(0.2f, 0.2f, 0.2f);
				footprint->SetRotate(0, 0, -(XM_PI / 6));
				//footprint->SetDrawActive(false); // �ŏ��͔�\��

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
