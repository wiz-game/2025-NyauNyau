
/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "PauseSprite.h"
#include "MainCamera.h"
#include "Phase1Camera.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------

	enum class GamePhase
	{
		Phase1,  //Box �̂ݑ���\
 	    Phase2   //�S�I�u�W�F�N�g������J�n

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
		//���f���̓Ǎ�
		void LoadModels();


		void CreateBox();
		//void CreateTestShadowBox();

		//�v���C���[�̐���
		void CreatePlayer();

		//�G�l�~�[�̐���
		void CreateEnemy();

		//�|�[�Y�t���O
		bool m_PauseFlag = false;
		bool m_pauseSprite = false;
		int m_SpriteNum;//���I�����Ă���X�v���C�g


		void ChangeSelect(int num);
		//����Y����ύX������֐�
		void SetSelectPosition(int SpriteNum);
		bool m_CntrolLock;
		float m_selectY;//����Y���W�̈ʒu
		float m_selectX;//����X���W�̈ʒu

		std::vector<std::weak_ptr<pauseSprite>> m_pauseSprites;//�|�[�Y�X�v���C�g�̕ϐ�
		std::shared_ptr<pauseSprite> leftPointSprite;//�����
		std::shared_ptr<pauseSprite> Pause;


		//���̓n���h���[
		InputHandler<GameStage> m_InputHandler;


		shared_ptr<SoundItem> m_BGM;

		shared_ptr<SingleView> m_mainView; // ���C���J�����ւ̎Q��
		shared_ptr<SingleView> m_phase1View;

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

		//�X�v���C�g�i���o�[�̃A�N�Z�T
		int GetSpriteNum() const
		{
			return m_SpriteNum;
		}

		void SetSpriteNum(int i)
		{
			m_SpriteNum = i;
		}

	};



}
//end basecross

