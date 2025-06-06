/*!
@file Character.h
@brief �^�C�g���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "TitleSprite.h"
#include "SettingStage.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		void CreateViewLight(); //�r���[�̍쐬
		void LoadTextures();//�e�N�X�`���̓Ǎ�
		void OnDestroy();

		//���̓n���h���[
		InputHandler<TitleStage> m_InputHandler;
		shared_ptr<SoundItem> m_BGM;
		std::vector<std::shared_ptr<TitleSprite>> m_titleSprite;
		std::weak_ptr<SettingStage> m_settingStage;
		
		const int spriteCount = 11;
		float phaseIncrement = 0.5f;
		float m_totalTime;


	public:
		//�\�z�Ɣj��
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}

		virtual void OnCreate()override; //������
		virtual void OnUpdate()override; //�X�V

		//A�{�^��
		void OnPushA();
		void OnPushB(){}
	};
}
//end basecross
