/*!
@file BackTitleButton.h
@brief �X�e�[�W�X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class GameStageUI : public GameObject;
	//--------------------------------------------------------------------------------------
	class GameStageUI : public GameObject
	{
		//�g�[�^������
		float m_totalTime;
		//�I�����Ă��邩�ǂ���
		bool m_Selected;
		float blinkSpeed = 3;//�_�ő��x


		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;


	public:
		// �\�z�Ɣj��
		GameStageUI(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~GameStageUI()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);


		//m_Selected�̃A�N�Z�T
		int IsSelected() const
		{
			return m_Selected;
		}

		void SetSelected(bool b)
		{
			m_Selected = b;
			m_totalTime = 0.0f;
		}
	};



}
//end basecross
