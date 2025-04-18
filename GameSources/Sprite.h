/*!
@file Sprite.h
@brief �^�C�g�����Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Sprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class Sprite : public GameObject
	{
	public:
		// �\�z�Ɣj��
		Sprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Sprite()
		{
		}

		virtual void OnCreate() override; // ������
		//virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};

}
//end basecross
