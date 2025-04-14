
/*!
@file SpotLight.h
@brief ���C�g�I�u�W�F�N�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpotLight : GameObject
	{
	public:
		//�R���X�g���N�^
		SpotLight(const shared_ptr<Stage>& stage) :
			GameObject(stage)

		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};


}
//end basecross

