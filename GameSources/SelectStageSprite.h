/*!
@file BackTitleButton.h
@brief �X�e�[�W�X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//�X�e�[�W�P
	//--------------------------------------------------------------------------------------
	//	class SelectStageSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class SelectStageSprite : public GameObject
	{
		//�g�[�^������
		float m_totalTime;
		//�I�����Ă��邩�ǂ���
		bool m_Selected;

		std::shared_ptr<PCTSpriteDraw> m_drawComp;

		

	public:
		// �\�z�Ɣj��
		SelectStageSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~SelectStageSprite()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
		void SetTexture(const std::wstring& Key);


		//m_Blinking�̃A�N�Z�T
		int IsSelected() const
		{
			return m_Selected;
		}

		void SetSelected()
		{
			m_Selected = false;
			m_totalTime = 0.0f;
		}

	};



}
//end basecross
