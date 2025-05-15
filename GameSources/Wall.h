
/*!
@file Wall.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	class Wall : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		Wall(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~Wall();

		void OnCreate() override;
		void OnUpdate() override;

		Vec3 GetWallNormal() const;
		Vec3 GetWallPosition() const;
	};


}
//end basecross
#pragma once
#pragma once
