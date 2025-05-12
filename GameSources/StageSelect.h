/*!
@file Character.h
@brief �^�C�g���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "Project.h"
#pragma once


namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class StageSelect : public Stage {
		void CreateViewLight(); //�r���[�̍쐬
		//void LoadTextures();//�e�N�X�`���̓Ǎ�
		//void OnDestroy();

		//���̓n���h���[
		InputHandler<StageSelect> m_InputHandler;
		//shared_ptr<SoundItem> m_BGM;



	public:
		//�\�z�Ɣj��
		StageSelect() :Stage() {}
		virtual ~StageSelect() {}

		virtual void OnCreate()override; //������
		virtual void OnUpdate()override; //�X�V

		//A�{�^��
		void OnPushA();


	};
	
	class SelectMassege :public StageSelect
	{
		//�ǂ̃V�[�������s���邩���Ǘ�
		enum class Scene
		{
			Start,//�X�^�[�g���
			Init,//�Q�[���̏�����
			Game,//�Q�[���V�[��
			End//�A�v���P�[�V�����̏I��
		};

		Scene currentScene;

	public:
		static int stageSelect;
		static const int stageMax = 3;

		static bool isPushEnter;
		static bool isPushDwon;
		static bool isPushUp;

		SelectMassege();

		void OnCreate();
		void OnUpdate();
		void drawScene();
		void isRunning();

	};
}
//end basecross
