/*!
@file gameClearSprite.h
@brief �Q�[���N���A �X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class gameClearSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class gameClearSprite : public GameObject
	{
	public:
		// �\�z�Ɣj��
		gameClearSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~gameClearSprite()
		{
		}

		virtual void OnCreate() override; // ������
		//virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};

}
//end basecross
