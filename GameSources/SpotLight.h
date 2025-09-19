
/*!
@file SpotLight.h
@brief ライトオブジェクトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class SpotLight : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		shared_ptr<PNTStaticModelDraw> m_drawComp;

	public:
		SpotLight(shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~SpotLight();
		void OnCreate() override;
		void OnUpdate() override;

		void InitDrawComp();

	};


}
//end basecross

