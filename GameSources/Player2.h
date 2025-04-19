
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
		void MoveToWallPosition(const shared_ptr<GameObject>& wall);
		//void GetPlayer(shared_ptr<GameObject>& Player);

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;


		//���̓n���h���[
		InputHandler<Player> m_InputHandler;
		//�X�s�[�h
		float m_Speed;
		float m_Player1;
		//�󒆂ɂ��邩
		bool m_isAir;

	public:
		//�\�z�Ɣj��
		Player(const shared_ptr<Stage>& StagePtr,
			Vec3& m_Scale,
		    Vec3& m_Rotation,
			Vec3& m_Position
		);

		virtual void SetPlayerMove(bool Player1);


		virtual ~Player() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;

		
		//A�{�^��
		void OnPushA();
	};
}
//end basecross

