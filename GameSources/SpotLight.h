
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
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
		shared_ptr<PNTStaticModelDraw> m_drawComp;

	public:
		SpotLight(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~SpotLight();
<<<<<<< Updated upstream

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
=======
		void OnCreate() override;
		void OnUpdate() override;
>>>>>>> Stashed changes

		void InitDrawComp();

	};


}
//end basecross

