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
	void PauseManager::PauseGame()
	{
		PlayGame(!IsPlaying());
	}

	void PauseManager::OnCreate()
	{
		auto stage = GetStage();
		//�|�[�Y���
		Pause = ObjectFactory::Create<PauseSprite>(GetStage());
		Pause->SetTexture(L"TEX_PAUSE");
		Pause->SetPosition(0, 0, 0);
		Pause->SetSelected(false);
		Pause->SetScale(1.5f, 1.5f, 0);

		//���X�^�[�g
		auto restart = ObjectFactory::Create<PauseSprite>(stage);
		restart->SetTexture(L"TEX_RESTART");
		restart->SetPosition(0, 20, 0);
		restart->SetScale(0.5f, 0.5f, 0.5f);
		restart->SetSelected(true);
		m_pauseSprites.push_back(restart);//m_pauseSprites��restart������

		//�^�C�g���ɖ߂�
		auto title = ObjectFactory::Create<PauseSprite>(stage);
		title->SetTexture(L"TEX_BACK");
		title->SetPosition(0, -70.0f, 0);
		title->SetScale(0.5f, 0.5f, 0.5f);
		m_pauseSprites.push_back(title);//m_pauseSprites��back������

		//�ݒ�
		auto setting = ObjectFactory::Create<PauseSprite>(stage);
		setting->SetTexture(L"TEX_SETTING");
		setting->SetPosition(0, -160.0f, 0);
		setting->SetScale(0.47f, 0.47f, 0.47f);
		m_pauseSprites.push_back(setting);//m_pauseSprites��end������

		//�I��
		auto end = ObjectFactory::Create<PauseSprite>(stage);
		end->SetTexture(L"TEX_END2");
		end->SetPosition(0, -250.0f, 0);
		end->SetScale(0.47f, 0.47f, 0.47f);
		m_pauseSprites.push_back(end);//m_pauseSprites��end������

		//�l�R���
		catPointSprite = ObjectFactory::Create<PauseSprite>(stage);
		catPointSprite->SetTexture(L"TEX_POINT");
		catPointSprite->SetPosition(m_selectX + (-200), m_selectY + 20, 0);
		catPointSprite->SetScale(0.2f, 0.2f, 0.2f);
		catPointSprite->SetSelected(false);

	}

	void PauseManager::OnDraw()
	{
		if (!m_isPlaying)
		{
			Pause->OnDraw();
			for (int i = 0; i < 4; i++)
			{
				m_pauseSprites[i]->OnDraw();
			}
			catPointSprite->OnDraw();
		}
	}

	void PauseManager::OnUpdate()
	{
		//�R���g���[���̎擾
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//�X�^�[�g�{�^�����������Ƃ��Ƀ{�[�Y����
		if (CntlVec[0].bConnected)
		{
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START)
			{
				PlayGame(!m_isPlaying);
			}

			if (!m_isPlaying)
			{
				Pause->OnUpdate();
				for (int i = 0; i < 4; i++)
				{
					m_pauseSprites[i]->OnUpdate();
				}
				catPointSprite->OnUpdate();

				m_SpriteNum = GetSpriteNum();
				//m_isPlaying = !m_isPlaying;

				//CntrolLock = false�̎�
				if (!m_CntrolLock)
				{
					for (int i = 0; i < 4; i++)
					{
						auto spriteNum = m_pauseSprites[i]->IsSelected();
					}

					//�����
					if (CntlVec[0].fThumbLY >= 0.8f)
					{
						m_SpriteNum--;
						//�X�e�[�W�P����ɃX�e�B�b�N�𓮂�������X�e�[�W�R�Ɉړ�
						if (m_SpriteNum < 0)
						{
							m_SpriteNum = 3;
						}
						m_CntrolLock = true;
						SetSpriteNum(m_SpriteNum);
						ChangeSelect(m_SpriteNum);
						SetSelectPosition(m_SpriteNum);
						//�|�C���g�X�v���C�g�̍��W�ύX
						if (catPointSprite)
						{
							catPointSprite->SetPosition(-250.0f, m_selectY, 0);
						}

					}
					//������
					else if (CntlVec[0].fThumbLY <= -0.8f)
					{
						m_SpriteNum++;
						//�X�e�[�W�R�ɗ�����X�e�[�W�P�ɖ߂�
						if (m_SpriteNum >= 4)
						{
							m_SpriteNum = 0;
						}
						m_CntrolLock = true;
						SetSpriteNum(m_SpriteNum);
						ChangeSelect(m_SpriteNum);
						SetSelectPosition(m_SpriteNum);
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



		if (!m_isPlaying)
		{
			if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				auto scene = App::GetApp()->GetScene<Scene>();
				switch (m_SpriteNum)
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
					PlayGame(!m_isPlaying);

					return;

				}
			}
		}
	}



	//�I�����Ă���Sprite��_�ł����鏈��
	void PauseManager::ChangeSelect(int m_SpriteNum)
	{
		for (int i = 0; i < 4; i++)
		{
			//StageNum��m_pauseSprites�ƈ�v���Ă�����
			if (i == m_SpriteNum)
			{

				m_pauseSprites[i]->SetSelected(true);

			}
			else
			{
				m_pauseSprites[i]->SetSelected(false);
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


};