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
	public:
		Ground(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate() override; // �����ݒ�p�̃C�x���g�n���h��
		void OnUpdate() override;
	};
}
//end basecross

