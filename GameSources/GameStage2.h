/*!
@file GameStage.h
@brief �Q�[���X�e�[�W2
*/

#pragma once
#include "stdafx.h"
#include "PauseSprite.h"
#include "MainCamera.h"
#include "PauseManager.h"
#include "Phase1Camera.h"
#include "SettingStage.h"
#include "GameStageUI.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	enum class GamePhase2
	{
		Phase1,  //Box �̂ݑ���\
		Phase2,   //�S�I�u�W�F�N�g������J�n

	};

	class GameStage2 : public Stage {

		//�r���[�̍쐬
		void CreateViewLight();
		//�ǂ̐���
		void CreateWall();
		//���̐���
		void CreateGround();
		//�I�̍쐬
		void CreateShadowFloor();
		//�X�^�[�g�̍쐬
		void CreatestartGate();
		//�S�[���̍쐬
		void CreategoalGate();
		//�e�[�u���̍쐬
		void CreateTable();

		//�e�N�X�`���̓Ǎ�
		void LoadTextures();
		//���f���̓Ǎ�
		void LoadModels();

		void CreateBox();


		//�v���C���[�̐���
		void CreatePlayer();

		//�G�l�~�[�̐���
		void CreateEnemy();


		shared_ptr<SingleView> m_mainView; // ���C���J�����ւ̎Q��
		shared_ptr<SingleView> m_phase1View;

		std::weak_ptr<PauseManager> m_pauseManager;//�|�[�Y�}�l�[�W���[�ւ̎Q��
		std::weak_ptr<SettingStage> m_settingStage;//�Z�b�e�B���O�X�e�[�W�ւ̎Q��
		std::vector<std::weak_ptr<GameStageUI>> m_gameStageUI;//UI�X�v���C�g�ւ̎Q��

		//���̓n���h���[
		InputHandler<GameStage2> m_InputHandler;

		shared_ptr<SoundItem> m_BGM;

		GamePhase2 currentPhase = GamePhase2::Phase1; // �ŏ��ɐݒ肳��Ă���Phase


	public:
		//�\�z�Ɣj��
		GameStage2() :Stage() {}
		virtual ~GameStage2() {}

		void OnPushA();


		//������		
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		virtual void OnDestroy()override;

	};
}
//end basecross
