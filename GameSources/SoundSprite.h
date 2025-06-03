/*!
@file BackTitleButton.h
@brief �X�e�[�W�X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class SoundSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class SoundSprite : public GameObject
	{
		//�g�[�^������
		float m_totalTime;
		//�I�����Ă��邩�ǂ���
		bool m_Selected;

		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;

		float m_width;
		float m_height;
		float m_sx;
		float m_sy;
		float m_ex;
		float m_ey;


	public:
		// �\�z�Ɣj��
		SoundSprite(const shared_ptr<Stage>& stage, float sx, float sy ,float ex, float ey) :
			GameObject(stage),
			m_sx(sx),
			m_sy(sy),
			m_ex(ex),
			m_ey(ey)

		{
		}
		virtual ~SoundSprite()
		{
		}

		virtual void OnCreate() override; // ������
		//virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);


		//m_Selected�̃A�N�Z�T
		int IsSelected() const
		{
			return m_Selected;
		}

		void SetSelected(bool b)
		{
			m_Selected = b;
			m_totalTime = 0.0f;
		}
	};



}
//end basecross
