/*!
@file pauseSprite.h
@brief �^�C�g�����Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class pauseSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class pauseSprite : public GameObject
	{
	public:
		// �\�z�Ɣj��
		pauseSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~pauseSprite()
		{
		}

		virtual void OnCreate() override; // ������
		//virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};

}
//end basecross
