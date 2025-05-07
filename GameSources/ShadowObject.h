/*!
@file ShadowObject.h
@brief �e�̎Z�o�E�`����s���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ShadowObject : public GameObject {
		std::shared_ptr<PCStaticDraw> m_drawComp;//�h���[�R���|�[�l���g

	public:
		Vec3 m_lightPos; //�����̈ʒu

		ShadowObject(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_lightPos(0)
		{
		}
		virtual ~ShadowObject()
		{
		}

		//�e�̔{�������߂�֐�
		float CalculateShadowScale(const Vec3& lightPos, const Vec3& objectPos, const Vec3& wallPoint, const Vec3& wallNormal);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};




}