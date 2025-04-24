/*!
@file ShadowObject.h
@brief 影の算出・描画を行うオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ShadowObject : public GameObject {
		Vec3 m_lightPos; //光源の位置
		std::shared_ptr<PCStaticDraw> m_drawComp;//ドローコンポーネント

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