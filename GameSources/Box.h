
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


		float m_Speed;

		bool m_isAir;

		const float m_gravity;

		bool m_isSelectedForControl; // ����Box�����݁A�v���C���[�ɂ���Ē��ڑ��삳���Ώۂ��������t���O

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
			 Vec3& Scale,
			 Vec3& Rotation,
			 Vec3& Position
		) :
			GameObject(stage),

			m_Scale(Scale),
			m_Rotation(Rotation),
			m_Position(Position),

			m_Speed(5.0f),
			m_isAir(false),
			m_gravity(-9.0),
			m_velocity(0.0f),
			m_isSelectedForControl(false)


		{
		}


		// ����Box������ΏۂƂ��đI�����ꂽ/�������ꂽ���ɌĂ΂��֐�
		void SetSelectedForControl(bool selected);
		// ����Box�����ݑ���Ώۂ��m�F����֐�
		bool IsSelectedForControl() const;


		virtual ~Box(){}

		std::vector<Vec3> GetBoxVertices() const;

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}
//end basecross

