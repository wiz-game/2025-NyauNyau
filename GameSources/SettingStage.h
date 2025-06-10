/*!
@file Character.h
@brief �X�e�[�W�Z���N�g���
*/

#pragma once
#include "stdafx.h"
#include "SoundSprite.h"
#include "GameStageUI.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�N���X
	//--------------------------------------------------------------------------------------
	class SettingStage : public Stage {
		void CreateViewLight(); //�r���[�̍쐬
		void LoadTextures();//�e�N�X�`���̓Ǎ�
		void OnDestroy();

		std::shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		std::vector<std::weak_ptr<SoundSprite>> m_BGMsoundSprites;//�T�E���h�X�v���C�g���Ǘ�����
		std::vector<std::weak_ptr<SoundSprite>> m_SEsoundSprites;//�T�E���h�X�v���C�g���Ǘ�����

		std::shared_ptr<SoundSprite> catPointSprite;
		std::shared_ptr<SoundSprite> Setting;
		bool volumeChanged = false;
		bool isBGMSelected = true;
		bool m_MenuNavigationLock = true;

		std::weak_ptr<GameStageUI> m_StageUI;


	public:
		//�\�z�Ɣj��
		SettingStage() :Stage()
		{
		}
		virtual ~SettingStage() {}

		virtual void OnCreate()override; //������
		virtual void OnUpdate()override; //�X�V


	};

}
//end basecross