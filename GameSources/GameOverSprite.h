/*!
@file GameOverSprite.h
@brief �Q�[���I�[�o�[�X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class GameOverSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class GameOverSprite : public GameObject
	{

	public:
		// �\�z�Ɣj��
		GameOverSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		virtual ~GameOverSprite()
		{
		}


		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};

}
//end basecross
