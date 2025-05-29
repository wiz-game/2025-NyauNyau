
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

	enum class GamePhase
	{
		Phase1,  //Box �̂ݑ���\
		Phase2,   //�S�I�u�W�F�N�g������J�n
		Phase3

	};
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
		//�I�̍쐬
		void CreateShadowFloor();
		//�e�N�X�`���̓Ǎ�
		void LoadTextures();

		void CreateBox();
		//void CreateTestShadowBox();

		//�v���C���[�̐���
		void CreatePlayer();

		//�G�l�~�[�̐���
		void CreateEnemy();

		bool m_PauseFlag = false;
		bool m_pauseSprite = false;

		std::shared_ptr<pauseSprite> m_Pause;

		//���̓n���h���[
		InputHandler<GameStage> m_InputHandler;


		shared_ptr<SoundItem> m_BGM;

		shared_ptr<MainCamera> m_mainCamera; // ���C���J�����ւ̎Q��

		GamePhase currentPhase = GamePhase::Phase1; // �ŏ��ɐݒ肳��Ă���Phase


		//std::shared_ptr<Box> boxObject;
		//std::vector<std::shared_ptr<GameObject>> gameObjects;

		

	public:
		//�\�z�Ɣj��
		GameStage() :Stage(){}
		virtual ~GameStage() {}
		void OnPushA();	

		//������		
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		virtual void OnDestroy()override;

		//void Initialize();

	};



}
//end basecross

