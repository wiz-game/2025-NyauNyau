/*!
@file Character.h
@brief �Q�[���I�[�o�[�X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "TitleSprite.h"
#include "CatwalkSprite.h"

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
		shared_ptr<SoundItem> m_SE;

		std::weak_ptr<CatWalkSprite> m_catSprite;
		std::vector<std::shared_ptr<GameObject>> m_sprites;

	public:
		//�\�z�Ɣj��
		GameOverStage() :Stage() {}
		virtual ~GameOverStage() {}

		virtual void OnCreate()override; //������
		virtual void OnUpdate()override; //�X�V

		//A�{�^��
		void OnPushA();
		void StartCatWalkAnimation();
	};
}
//end basecross
