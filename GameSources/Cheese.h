/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Cheese : public GameObject
	{
		shared_ptr<Transform> m_transComp;
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;


	public:
		// �\�z�Ɣj��
		Cheese(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~Cheese();

		virtual void OnCreate() override; //������
		//virtual void OnUpdate() override; //�X�V


	};

}
//end basecross
