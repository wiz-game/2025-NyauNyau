/*!
@file pauseSprite.h
@brief �^�C�g�����Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class pauseSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class pauseSprite : public GameObject
	{
	public:
		float m_totalTime;//�g�[�^������
		bool m_Selected;//�I�����Ă��邩�ǂ���


		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;

		// �\�z�Ɣj��
		pauseSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~pauseSprite()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
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
