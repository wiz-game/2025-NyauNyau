
/*!
@file Box.h
@brief ���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Box : public GameObject
	{
	public:
		//�R���X�g���N�^
		Box(const shared_ptr<Stage>& stage) :
			GameObject(stage)

		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}
//end basecross
#pragma once

