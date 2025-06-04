/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Enemy :public GameObject
	{
		std::shared_ptr<Transform> m_transComp;
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		bool isGameOver;//�Q�[���I�[�o�[���Ǘ�
		float EnemySpeed;

		//�t�H�[�X
		Vec3 m_Force;
		//���x
		Vec3 m_Velocity;


	public:
		// �\�z�Ɣj��
		Enemy(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
			
		);

		const Vec3& GetForce()const {
			return m_Force;
		}
		void SetForce(const Vec3& f) {
			m_Force = f;
		}
		void AddForce(const Vec3& f) {
			m_Force += f;
		}

		const Vec3& GetVelocity()const {
			return m_Velocity;
		}
		void SetVelocity(const Vec3& v) {
			m_Velocity = v;
		}

		void ApplyForce();

		Vec3 GetTargetPos()const;




		virtual ~Enemy();

		virtual void OnCreate() override; //������
		virtual void OnUpdate() override; //�X�V


		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other) override;




	};

}
//end basecross