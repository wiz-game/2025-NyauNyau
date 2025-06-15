#pragma once
#include "stdafx.h"

namespace basecross 
{
	class ShadowBall : public GameObject
	{

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;


		float m_Speed;
		void DrawStrings();

		shared_ptr<PNTStaticDraw> m_drawComp;
		shared_ptr<Transform> m_transComp;


	public:
		//コンストラクタ
		ShadowBall(const shared_ptr<Stage>& stage,
			Vec3& Scale,
			Vec3& Rotation,
			Vec3& Position
		):
			GameObject(stage),
			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position),
			m_Speed(5.0f)

		{
		}

		virtual ~ShadowBall() {}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}

