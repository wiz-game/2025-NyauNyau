/*!
@file Character.h
@brief �X�e�[�W�Z���N�g���
*/

#pragma once
#include "stdafx.h"
#include "SelectStageSprite.h"
#include "FootprintSprite.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�N���X
	//--------------------------------------------------------------------------------------
	class SelectStage : public Stage {
		void CreateViewLight(); //�r���[�̍쐬
		void LoadTextures();//�e�N�X�`���̓Ǎ�
		void OnDestroy();
		shared_ptr<SoundItem> m_BGM;

		std::vector<std::weak_ptr<SelectStageSprite>> m_stageSprites;//�X�e�[�W�X�v���C�g���Ǘ�����
		std::vector<std::weak_ptr<FootprintSprite>> m_footprints;//���Ղ̊Ǘ�
		std::shared_ptr<FootprintSprite> m_transFootprints;

		std::shared_ptr<SelectStageSprite> catPointSprite;

		void ChangeSelect(int num);
		bool m_CntrolLock;
		float m_select;//���̈ʒu
		bool footprintsStart;
		//bool m_isWalking;//�l�R�������Ă��邩�ǂ����̔���

		//����Y����ύX������֐�
		void SetSelectYPosition(int StageNum);

		//�l�R�̑��Ղ̏���
		void CreateFootprints();
		//void CatWalk();//�l�R����������


	public:
		//�\�z�Ɣj��
		SelectStage() :Stage(),m_CntrolLock(false),footprintsStart(false)
		{
		}
		virtual ~SelectStage() {}

		virtual void OnCreate()override; //������
		virtual void OnUpdate()override; //�X�V

	};
	
}
//end basecross