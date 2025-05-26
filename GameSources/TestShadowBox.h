#pragma once

#include "stdafx.h"

namespace basecross
{
	class TestShadowBox : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;


	public:
		//ç\ízÇ∆îjä¸
		TestShadowBox(const shared_ptr<Stage>& StagePtr,
			 Vec3& Scale,
			 Vec3& Rotation,
			 Vec3& Position

		);


		virtual ~TestShadowBox() {}

		void OnCreate();
		void OnUpdate();

	};
}