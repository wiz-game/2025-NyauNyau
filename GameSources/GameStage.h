
/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

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
		void LoadTextures();

		
		//�v���C���[�̐���
		void CreatePlayer();

	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
	};



}
//end basecross

