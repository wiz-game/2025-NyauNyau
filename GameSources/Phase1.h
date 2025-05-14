#pragma once
#include "stdafx.h"

namespace basecross
{

	class Phase1 : public GameObject 
	{

		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::shared_ptr<GameObject> boxObject;
		std::shared_ptr<Player> player;

		//���̓n���h���[
		InputHandler<Player> m_InputHandler;

		Vec2 GetInputState() const;
		bool m_Phase1;
		bool m_CollisionEnabled;
		bool isFrozen = true; // ������Ԃœ����~


	public:
		//�\�z�Ɣj��
		Phase1(const shared_ptr<Stage>& StagePtr
		);

		void Initialize();
		//void SetCollisionEnabled(bool enabled);



		virtual ~Phase1() {}
		//�A�N�Z�T
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;

	};


}