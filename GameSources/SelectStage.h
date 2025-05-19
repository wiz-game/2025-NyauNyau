/*!
@file Character.h
@brief �X�e�[�W�Z���N�g���
*/

#pragma once
#include "stdafx.h"
#include "SelectStageSprite.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�N���X
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		void CreateViewLight(); //�r���[�̍쐬
		void LoadTextures();//�e�N�X�`���̓Ǎ�
		//void OnDestroy();
		//shared_ptr<SoundItem> m_BGM;

		std::vector<std::weak_ptr<SelectStageSprite>> m_stageSprites;
		std::shared_ptr<SelectStageSprite> leftPointSprite;

		void ChangeSelect(int num);
		bool m_CntrolLock;
		float m_select;//���̈ʒu
		//void DrawString();

		//����Y����ύX������֐�
		void SetSelectYPosition(int StageNum);


	public:
		//�\�z�Ɣj��
		SelectStage() :Stage(),m_CntrolLock(false)
		{
		}
		virtual ~SelectStage() {}

		virtual void OnCreate()override; //������
		virtual void OnUpdate()override; //�X�V

	};
	
}
//end basecross