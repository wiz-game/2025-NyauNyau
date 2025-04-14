/*!
@file Character.h
@brief �X�^�[�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class startGate : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//�\�z�Ɣj��
		startGate(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~startGate();
		//������
		virtual void OnCreate() override;

	};

}
//end basecross
