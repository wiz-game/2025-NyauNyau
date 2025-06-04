/*!
@file Character.h
@brief �Q�[���I�[�o�[�X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "TitleSprite.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�I�[�o�[�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameOverStage : public Stage {
		void CreateViewLight(); //�r���[�̍쐬
		void LoadTextures();//�e�N�X�`���̓Ǎ�
		void OnDestroy();

		//���̓n���h���[
		InputHandler<GameOverStage> m_InputHandler;
		shared_ptr<SoundItem> m_BGM;
		//std::vector<std::shared_ptr<GameOverSprite>> m_GameOverSprite;

	public:
		//�\�z�Ɣj��
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}

		virtual void OnCreate()override; //������
		virtual void OnUpdate()override; //�X�V

		//A�{�^��
		void OnPushA();

	};
}
//end basecross
