
/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "PauseSprite.h"
#include "MainCamera.h"
#include "PauseManager.h"
#include "Phase1Camera.h"
#include "SettingStage.h"
#include "GameStageUI.h"
//#include  "cmath"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------

	enum class GamePhase
	{
		Phase1,  //Box �̂ݑ���\
 	    Phase2,   //�S�I�u�W�F�N�g������J�n

	};

	enum class GameControlMode 
	{
		SelectBox,  // ���݁A���삷��Box��I�����Ă���Œ��ł��邱�Ƃ��������[�h
		ControlBox  // �����Box��I�����A����Box�𑀍삵�Ă���Œ��ł��邱�Ƃ��������[�h
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
		//�e�[�u���̍쐬
		void CreateTable();
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

		void CreateShadowBall();

		std::weak_ptr<PauseManager> m_pauseManager;//�|�[�Y�}�l�[�W���[�ւ̎Q��
		std::weak_ptr<SettingStage> m_settingStage;//�Z�b�e�B���O�X�e�[�W�ւ̎Q��
		std::vector<std::weak_ptr<GameStageUI>> m_gameStageUI;//UI�X�v���C�g�ւ̎Q��

		//���̓n���h���[
		InputHandler<GameStage> m_InputHandler;

		shared_ptr<SoundItem> m_BGM;

		shared_ptr<SingleView> m_mainView; // ���C���J�����ւ̎Q��
		shared_ptr<SingleView> m_phase1View;

		GamePhase currentPhase = GamePhase::Phase1; // �ŏ��ɐݒ肳��Ă���Phase

		std::vector<std::shared_ptr<Box>> m_controllableBoxes;
		// SelectBox���[�h�̎��ɁA�n�C���C�g����Ă���Box
		int m_selectedBoxIndex;

		// ���݂̃Q�[���̑��샂�[�h�iSelectBox �� ControlBox ���j��ێ�����
		GameControlMode m_currentControlMode;
		// ControlBox���[�h�̎��ɁA���ݎ��ۂɑ���ΏۂƂȂ��Ă���Box�I�u�W�F�N�g�ւ̃|�C���^
		std::shared_ptr<Box> m_currentlyControlledBox;
		
		bool m_stickMovedLeftLastFrame;  // �O�̃t���[���ō��ɓ|����Ă�����
        bool m_stickMovedRightLastFrame; // �O�̃t���[���ŉE�ɓ|����Ă�����

		//std::shared_ptr<Box> boxObject;
		//std::vector<std::shared_ptr<GameObject>> gameObjects;
		float m_Time;
		bool m_isStageFadingOut;
		float m_fadeTimer;
		float m_filterFadeTimer;

		

	public:
		//�\�z�Ɣj��
		GameStage() :
			Stage(),
			m_Time(0.0f),
			m_isStageFadingOut(false),
			m_fadeTimer(0.0f),
			m_filterFadeTimer(0.0f)
		{}
		virtual ~GameStage() {}


		void OnPushA();	

		// ���݂̑��샂�[�h���擾����֐�
		GameControlMode GetCurrentControlMode() const;
		// ���݃n�C���C�g����Ă���Box�𑀍�Ώۂɐݒ肵�AControlBox���[�h�ֈڍs���悤�Ǝ��݂�֐�
		void AttemptToControlSelectedBox();
		// ���ݑ��쒆��Box�̑�����I�����ASelectBox���[�h�֖߂�֐�
		void ReleaseControlOfBox();

		// SelectBox���[�h�ŁA����Box��I�����Ƃ��ăn�C���C�g���邽�߂̊֐�
		void SelectNextBox();
		// SelectBox���[�h�ŁA�O��Box��I�����Ƃ��ăn�C���C�g���邽�߂̊֐�
		void SelectPreviousBox();


		//������		
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnUpdate2()override;
		virtual void OnDestroy()override;


	};
}
//end basecross

