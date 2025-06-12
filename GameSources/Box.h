
/*!
@file Box.h
@brief ���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Box : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		Vec2 GetInputState() const;

		Vec3 GetMoveVector() const;



		InputHandler<Box> m_InputHandler;

		shared_ptr<PNTStaticModelDraw> m_drawModelComp;

		float m_Speed;

		bool m_isAir;

		const float m_gravity;

		Vec3 m_forward; // �O�����������x�N�g��
		Vec3 m_velocity;

		void MoveXZ();
		void BoxMove();
		void DrawStrings();

		shared_ptr<PNTStaticDraw> m_drawComp;
		shared_ptr<Transform> m_transComp;


	public:
		//�R���X�g���N�^
		Box(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		) :
			GameObject(stage),

			m_Speed(5.0f),
			m_isAir(false),
			m_gravity(-9.0),
			m_velocity(0.0f)


		{
		}

		virtual ~Box(){}

		std::vector<Vec3> GetBoxVertices() const;

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void InitDrawComp();

	};

}
//end basecross

