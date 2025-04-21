/*!
@file Character.h
@brief �S�[��
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class goalGate : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		std::shared_ptr<bool> m_gameClear;//shared_ptr�ŊǗ�
	public:
		//�\�z�Ɣj��
		goalGate(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~goalGate();
		//������
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//gameClear�̃Q�b�^�[
		std::shared_ptr<bool> GetGameClearFlag() const { return m_gameClear; }
	};

}
//end basecross
