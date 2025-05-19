
/*!
@file Box.h
@brief 箱オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Box : public GameObject
	{

		Vec2 GetInputState() const;

		Vec3 GetMoveVector() const;

		float m_Speed;

		bool m_isAir;

		const float m_gravity;

		Vec3 m_forward; // 前方向を示すベクトル
		Vec3 m_velocity;

		void MoveXZ();
		void BoxMove();

	public:
		//コンストラクタ
		Box(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_Speed(5.0f),
			m_isAir(false),
			m_gravity(-9.0)

		{
		}

		virtual ~Box(){}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}
//end basecross
#pragma once

