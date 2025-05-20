
/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "PauseSprite.h"
#include "MainCamera.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		//�ǂ̐���
		void CreateWall();
		//���̐���
		void CreateGround();
		//�X�^�[�g�̍쐬
		void CreatestartGate();
		//�S�[���̍쐬
		void CreategoalGate();
		//�`�[�Y�̍쐬
		void CreateCheese();
		//�e�N�X�`���̓Ǎ�
		void LoadTextures();

		void CreateBox();
		
		//�v���C���[�̐���
		void CreatePlayer();

		//�|�[�Y�t���O
		bool m_PauseFlag = false;
		bool m_pauseSprite = false;

		std::shared_ptr<pauseSprite> m_Pause;

		void ChangeSelect(int num);
		bool m_CntrolLock;
		float m_select;//���̈ʒu

		std::vector<std::weak_ptr<pauseSprite>> m_pauseSprites;//�|�[�Y�X�v���C�g�̕ϐ�
		std::shared_ptr<pauseSprite> leftPointSprite;//�����


		//���̓n���h���[
		//InputHandler<GameStage> m_InputHandler;


		shared_ptr<SoundItem> m_BGM;

		shared_ptr<MainCamera> m_mainCamera; // ���C���J�����ւ̎Q��


	public:
		//�\�z�Ɣj��
		GameStage() :Stage(){}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void OnPushA();
		virtual void OnDestroy()override;

	};



}
//end basecross

