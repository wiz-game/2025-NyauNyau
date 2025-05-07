/*!
@file ShadowObject.h
@brief 影の算出・描画を行うオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ShadowObject : public GameObject {
		std::shared_ptr<PCStaticDraw> m_drawComp;//ドローコンポーネント

	public:
		Vec3 m_lightPos; //光源の位置

		ShadowObject(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_lightPos(0)
		{
		}
		virtual ~ShadowObject()
		{
		}

		//影の倍率を求める関数
		float CalculateShadowScale(const Vec3& lightPos, const Vec3& objectPos, const Vec3& wallPoint, const Vec3& wallNormal);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};




}