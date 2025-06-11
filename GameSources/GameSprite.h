/*!
@file BackTitleButton.h
@brief �X�e�[�W�X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class GameSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class GameSprite : public GameObject
	{
		//�g�[�^������
		float m_totalTime;
		float m_speed = 50;//���x

		bool m_isMoving = false;
		float m_moveDirection = 1.0f;//�ړ������i1.0�F�E�@-1.0�F���j
		float m_moveRange = 15.0f;//�ړ��͈�

		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;


	public:
		// �\�z�Ɣj��
		GameSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~GameSprite()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);


		void SetMovementActive(bool IsActive)
		{
			m_isMoving = IsActive;
		}
	};



}
//end basecross
