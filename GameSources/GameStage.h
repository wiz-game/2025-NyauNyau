
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

		//�|�[�Y�t���O
		bool m_PauseFlag = false;
		//std::weak_ptr<PauseManager> m_pauseManager;//�|�[�Y�}�l�[�W���[�ւ̎Q��

		//���̓n���h���[
		//InputHandler<GameStage> m_InputHandler;


		shared_ptr<SoundItem> m_BGM;

		shared_ptr<MainCamera> m_mainCamera; // ���C���J�����ւ̎Q��

		GamePhase currentPhase = GamePhase::Phase1;


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

