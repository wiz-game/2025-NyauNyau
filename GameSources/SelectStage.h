/*!
@file Character.h
@brief �X�e�[�W�Z���N�g���
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�N���X
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		void CreateViewLight(); //�r���[�̍쐬
		void LoadTextures();//�e�N�X�`���̓Ǎ�
		//void OnDestroy();
		//shared_ptr<SoundItem> m_BGM;

		std::vector<std::shared_ptr<SelectStageSprite>> m_stageSprites;

		void ChangeSelect(int um);
		//void DrawString();


	public:
		//�\�z�Ɣj��
		SelectStage() :Stage() {}
		virtual ~SelectStage() {}

		virtual void OnCreate()override; //������
		virtual void OnUpdate()override; //�X�V


		bool m_CntrolLock;


	};
	
}
//end basecross
