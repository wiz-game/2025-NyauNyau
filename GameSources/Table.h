#pragma once
/*!
@file Ground.h
@brief �L�����N�^�[�Ȃ�
*/
#include "stdafx.h"


namespace basecross {

	//�X�e�[�W�ɒǉ��\�Ȓn�ʂ�\���N���X
	class Table : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		shared_ptr<PNTStaticModelDraw> m_drawComp;


	public:
		Table (const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~Table();


		void OnCreate() override; // �����ݒ�p�̃C�x���g�n���h��
		void OnUpdate() override;

		void InitDrawComp();

	};
}
//end basecross
