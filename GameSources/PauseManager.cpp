/*
@file PauseManager.cpp
@brief �{�[�Y�}�l�[�W���[�̎���
*/

#include "stdafx.h"
#include "Project.h"
#pragma once

namespace basecross {

	//----------------------------------------------------------------------------------------------------------------
	// �|�[�Y�}�l�[�W���[�N���X����
	// ---------------------------------------------------------------------------------------------------------------
	void PauseManager::OnCreate()
	{

	}

	void PauseManager::OnUpdate()
	{
		if (!m_isPlaying)
		{

			//�R���g���[���̎擾
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			//�X�^�[�g�{�^�����������Ƃ��Ƀ{�[�Y����
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START)
			{
				//�V�[���̎擾
				auto scene = App::GetApp()->GetScene<Scene>();
				scene->PauseGame();
				int SpriteNum = GetSpriteNum();


				m_isPlaying = !m_isPlaying;

				//�|�[�Y�̃X�v���C�g��\������
				//for (int i = 0; i < 4; i++)
				//{
				//	std::shared_ptr<pauseSprite> sprites = m_pauseSprites[i].lock();
				//	sprites->SetDrawActive(true);
				//}
				//catPointSprite->SetDrawActive(true);
				//Pause->SetDrawActive(true);


				if (CntlVec[0].bConnected)
				{
					//A�{�^�����������Ƃ��ɃQ�[���X�e�[�W�Ɉړ�����
					if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
					{
						switch (SpriteNum)
						{
						case 0://���X�^�[�g
							PostEvent(0.0f, GetThis<PauseManager>(), scene, L"ToGameStage");
							return;

						case 1://�^�C�g��
							PostEvent(0.0f, GetThis<PauseManager>(), scene, L"ToTitleStage");
							return;

						case 2://�ݒ�
							PostEvent(0.0f, GetThis<PauseManager>(), scene, L"ToSettingStage");
							return;

						case 3://�I��
							return;

						}
					}

					//CntrolLock = false�̎�
					if (!m_CntrolLock)
					{
						//�����
						if (CntlVec[0].fThumbLY >= 0.8f)
						{
							SpriteNum--;
							//�X�e�[�W�P����ɃX�e�B�b�N�𓮂�������X�e�[�W�R�Ɉړ�
							if (SpriteNum < 0)
							{
								SpriteNum = 4;
							}
							m_CntrolLock = true;
							SetSpriteNum(SpriteNum);
							ChangeSelect(SpriteNum);
							SetSelectPosition(SpriteNum);
							//�|�C���g�X�v���C�g�̍��W�ύX

							if (catPointSprite)
							{
								catPointSprite->SetPosition(-250.0f, m_selectY, 0);
							}

						}
						//������
						else if (CntlVec[0].fThumbLY <= -0.8f)
						{
							SpriteNum++;
							//�X�e�[�W�R�ɗ�����X�e�[�W�P�ɖ߂�
							if (SpriteNum >= 4)
							{
								SpriteNum = 0;
							}
							m_CntrolLock = true;
							SetSpriteNum(SpriteNum);
							ChangeSelect(SpriteNum);
							SetSelectPosition(SpriteNum);
							//�|�C���g�X�v���C�g�̍��W�ύX
							if (catPointSprite)
							{
								catPointSprite->SetPosition(-250.0f, m_selectY, 0);
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

			}
			else
			{
				//�|�[�Y�̃X�v���C�g���\���ɂ���
				//for (int i = 0; i < 4; i++)
				//{
				//	std::shared_ptr<pauseSprite> sprites = m_pauseSprites[i].lock();
				//	sprites->SetDrawActive(false);
				//}
				//catPointSprite->SetDrawActive(false);
				//Pause->SetDrawActive(false);

				m_isPlaying = false;
				m_CntrolLock = false;
			}
		}
	}

	//�I�����Ă���Sprite��_�ł����鏈��
	void PauseManager::ChangeSelect(int num)
	{
		for (int i = 0; i < 4; i++)
		{
			std::shared_ptr<pauseSprite> srptr = m_pauseSprites[i].lock();
			if (srptr)
			{
				//StageNum��m_pauseSprites�ƈ�v���Ă�����
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
	void PauseManager::SetSelectPosition(int SpriteNum)
	{
		switch (SpriteNum)
		{
		case 0:
			m_selectX = -200.0f;
			m_selectY = 20.0f;
			break;
		case 1:
			m_selectX = -250.0f;
			m_selectY = -70;
			break;
		case 2:
			m_selectX = -200.0f;
			m_selectY = -160.0f;
			break;
		case 3:
			m_selectX = -100.0f;
			m_selectY = -250.0f;
			break;
		default:
			break;
		}
	}

	void PauseManager::PauseGame()
	{
		PlayGame(!IsPlaying());

		////�|�[�Y���
		//Pause = AddGameObject<pauseSprite>();
		//Pause->SetTexture(L"TEX_PAUSE");
		//Pause->SetPosition(0, 0, 0);
		//Pause->SetScale(1.5f, 1.5f, 0);

		////���X�^�[�g
		//auto restart = AddGameObject<pauseSprite>();
		//restart->SetTexture(L"TEX_RESTART");
		//restart->SetPosition(0, 20, 0);
		//restart->SetScale(0.5f, 0.5f, 0.5f);
		//restart->SetSelected(true);
		//m_pauseSprites.push_back(restart);//m_pauseSprites��restart������

		////�^�C�g���ɖ߂�
		//auto title = AddGameObject<pauseSprite>();
		//title->SetTexture(L"TEX_BACK");
		//title->SetPosition(0, -70.0f, 0);
		//title->SetScale(0.5f, 0.5f, 0.5f);
		//m_pauseSprites.push_back(title);//m_pauseSprites��back������

		////�ݒ�
		//auto setting = AddGameObject<pauseSprite>();
		//setting->SetTexture(L"TEX_SETTING");
		//setting->SetPosition(0, -160.0f, 0);
		//setting->SetScale(0.47f, 0.47f, 0.47f);
		//m_pauseSprites.push_back(setting);//m_pauseSprites��end������

		////�I��
		//auto end = AddGameObject<pauseSprite>();
		//end->SetTexture(L"TEX_END");
		//end->SetPosition(0, -250.0f, 0);
		//end->SetScale(0.47f, 0.47f, 0.47f);
		//m_pauseSprites.push_back(end);//m_pauseSprites��end������

		////�l�R���
		//catPointSprite = AddGameObject<pauseSprite>();
		//catPointSprite->SetTexture(L"TEX_POINT");
		//catPointSprite->SetPosition(m_selectX + (-200), m_selectY + 20, 0);
		//catPointSprite->SetScale(0.2f, 0.2f, 0.2f);

	}

}