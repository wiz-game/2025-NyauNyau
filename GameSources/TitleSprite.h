/*!
@file TitleSprite.h
@brief �^�C�g�����Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class TitleSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject
	{
		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;
		float m_totalTime;

		Vec3 m_basePosition;//��ʒu
		float frequency = 2.0f;// ����

	public:
		float m_phaseOffset = 0.0f;//�e�X�v���C�g���ɈقȂ�l���Z�b�g
		float m_amplitude = 10.0f;  // sin�g�̕�

		// �\�z�Ɣj��
		TitleSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_totalTime(0.0f)
		{
		}

		virtual ~TitleSprite()
		{
		}


		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��

		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);
	};

}
//end basecross
