#pragma once
#include "stdafx.h"

namespace basecross
{

	class Phase1: public GameObject
	{
	public:
		// �\�z�Ɣj��
		Phase1(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Phase1()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};



}