
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
		//�v���C���[�̈ړ�
		void MovePlayer();

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;


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


		virtual ~Player() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;


	};
}
//end basecross

