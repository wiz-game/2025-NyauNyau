#pragma once
/*!
@file Ground.h
@brief �L�����N�^�[�Ȃ�
*/
#include "stdafx.h"


namespace basecross {

	//�X�e�[�W�ɒǉ��\�Ȓn�ʂ�\���N���X
	class Ground : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		Ground(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~Ground();


		void OnCreate() override; // �����ݒ�p�̃C�x���g�n���h��
		void OnUpdate() override;
	};
}
//end basecross

