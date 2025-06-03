/*!
@file BackgroundTitleSprite.h
@brief �^�C�g�����Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class BackgroundTitleSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class BackgroundTitleSprite : public GameObject
	{

	public:
		// �\�z�Ɣj��
		BackgroundTitleSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		virtual ~BackgroundTitleSprite()
		{
		}


		virtual void OnCreate() override; // ������
		//virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};

}
//end basecross
