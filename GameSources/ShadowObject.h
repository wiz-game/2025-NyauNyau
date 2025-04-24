/*!
@file ShadowObject.h
@brief �e�̎Z�o�E�`����s���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ShadowObject : public GameObject {
		Vec3 m_lightPos; //�����̈ʒu
		std::shared_ptr<PCStaticDraw> m_drawComp;//�h���[�R���|�[�l���g

	public:
		ShadowObject(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_lightPos(0)
		{
		}
		virtual ~ShadowObject()
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};




}