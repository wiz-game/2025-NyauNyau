#pragma once
/*!
@file MainCamera.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class MainCamera : public Camera;
	//--------------------------------------------------------------------------------------
	class MainCamera : public Camera
	{
		// �����ΏۃI�u�W�F�N�g
		std::weak_ptr<GameObject> m_targetObj;

		float m_height; // �J�����̍���
		float m_distance; // �����_��̋���
		float m_angleY; // Y�����S�̃J�����̉�荞��

	public:
		// �\�z�Ɣj��
		MainCamera(const shared_ptr<Stage>& stage) :
			m_height(4.5f),
			m_distance(4.0f),
			m_angleY(-XM_PIDIV2) // �u��/2�v���W�A�����u90���v
		{
		}

		virtual ~MainCamera()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V

		// �����Ώۂ�ݒ肷��֐�
		void SetTargetObject(const shared_ptr<GameObject>& object)
		{
			m_targetObj = object;
		}
	};

}
//end basecross
