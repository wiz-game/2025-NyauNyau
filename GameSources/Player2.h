
/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
		//�v���C���[���g�p����R���g���[���̓���
		Vec2 GetInputState() const;
		// �R���g���[����������x�N�g���𓾂�
		Vec3 GetMoveVector() const;
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		Col4 m_color;
		std::vector<VertexPositionColorTexture> m_vertices;
		std::vector<uint16_t> m_indices;

		int m_number;
		//���̓n���h���[
		InputHandler<Player> m_InputHandler;
		//�X�s�[�h
		float m_Speed;

		bool m_Player1;

		//�󒆂ɂ��邩
		bool m_isAir;

		float m_cameraAngleY; // �J�����̉�荞��
		float m_velocityY;
		Vec3 m_forward; // �O�����������x�N�g��
		Vec3 m_velocity;
		bool m_collisionFlag;
		const float m_gravity;
	
		void MoveY();
		void MoveXZ();
		void OnCollisionExcute(shared_ptr<GameObject>& Other);
		void OnCollisionExit(shared_ptr<GameObject>& Other);
		void Jump(shared_ptr<GameObject>& jump);
	    void DrawStrings();

		shared_ptr<PNTStaticDraw> m_drawComp; // �W���I�ȃA�j���[�V���������̃h���[�R���|�[�l���g

		// BaseCross��ŕK�v�Ȏ��g�̏��
		shared_ptr<Transform> m_Transform;

		// ���g�̏��
		Vec3 m_Center;
		float m_Radius;

		// �Փˑ���̏��
		shared_ptr<ShadowObject> m_OtherPolygon;

	

	public:
		//�\�z�Ɣj��
		Player(const shared_ptr<Stage>& StagePtr,
			Vec3& m_Scale,
		    Vec3& m_Rotation,
			Vec3& m_Position
		);

		void SetPlayerMove(bool Player1);

		//A�{�^��
		void OnPushA();



		// �J�����̉�荞�݂�ݒ肷��
		void SetCameraAngleY(float angleY)
		{
			m_cameraAngleY = angleY;
		}


		void SetCenter(const Vec3& center)
		{
			m_Center = center;
		}

		Vec3 GetCenter() const
		{
			return m_Center;
		}

		//�v���C���[�̈ړ�
		void MovePlayer();

		//Vec2 GetNormal(const Vec2& a, const Vec2& b)
		//{
		//	Vec2 edge = Vec2(b.x - a.x, b.y - a.y);
		//	return Vec2(-edge.y, edge.x).normalize();
		//}
		
		// �x�N�g���̖@���i�����̕������j���擾
		Vec3 GetNormal(const Vec3& a, const Vec3& b)
		{
			Vec2 edge = Vec2(b.x - a.x, b.y - a.y);
			return Vec3(-edge.y, edge.x,0.0f).normalize();

		}

		// ���p�`�𕪗����ɓ��e���Ĕ͈͂��擾
		void ProjectOntoAxis(const vector<Vec3>& poly, const Vec3& axis, float& min, float& max)
		{
			min = max = poly[0].dot(axis);
			for (const auto& p : poly)
			{
				float proj = p.dot(axis);
				if (proj < min) min = proj;
				if (proj > max) max = proj;
			}
		}

		// �~�𕪗����ɓ��e���Ĕ͈͂��擾
		void ProjectCircleOntoAxis(const Vec3& center, float radius, const Vec3& axis, float& min, float& max)
		{
			float centerProj = center.dot(axis);
			min = centerProj - radius;
			max = (centerProj + radius) * 10;
		}


		// �~�Ɠʑ��p�`�̍ŏ������o���x�N�g���iMTV�j�����߂�
		bool ComputeMTV(const std::vector<Vec3>& polygonVertices, Vec3& mtv);
		//bool ComputeMTV(const shared_ptr<ShadowObject>& polygon, const Vec3& sphereWorldCenter, float sphereRadius, Vec3& mtv); // �ύX��


		virtual ~Player() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;

		//void OnCollisionEnter(shared_ptr<GameObject>& collision) override;




	};
}
//end basecross

