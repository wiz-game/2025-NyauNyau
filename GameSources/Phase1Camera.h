/*!
@file Phse1Camera.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class Phase1Camera : public Camera;
	//--------------------------------------------------------------------------------------
	class Phase1Camera : public Camera
	{
		float m_height; // �J�����̍���
		float m_distance; // �����_��̋���
		float m_angleY; // Y�����S�̃J�����̉�荞��

	public:
		// �\�z�Ɣj��
		Phase1Camera() :
			m_height(0.0f),
			m_distance(0.0f),
			m_angleY(90.0f) // �u��/2�v���W�A�����u90���v
		{
		}

		virtual ~Phase1Camera()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V

	};

}
//end basecross
