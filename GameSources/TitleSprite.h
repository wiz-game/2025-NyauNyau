/*!
@file TitleSprite.h
@brief �^�C�g�����Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class TitleSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject
	{
	public:
		// �\�z�Ɣj��
		TitleSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~TitleSprite()
		{
		}

		virtual void OnCreate() override; // ������
		//virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};

}
//end basecross
