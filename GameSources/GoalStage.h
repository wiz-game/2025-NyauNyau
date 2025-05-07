/*!
@file Character.h
@brief �S�[���^�C�g���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�S�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class goalStage : public Stage {
		void CreateViewLight(); //�r���[�̍쐬
		void LoadTextures();//�e�N�X�`���̓Ǎ�


		//���̓n���h���[
		InputHandler<goalStage> m_InputHandler;
		shared_ptr<SoundItem> m_BGM;


	public:
		//�\�z�Ɣj��
		goalStage() :Stage() {}
		virtual ~goalStage() {}

		virtual void OnCreate()override; //������
		virtual void OnUpdate()override; //�X�V

		//A�{�^��
		void OnPushA();
		void OnDestroy();

	};
}
//end basecross
