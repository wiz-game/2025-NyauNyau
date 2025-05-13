/*!
@file BackTitleButton.h
@brief �X�e�[�W�X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//�X�e�[�W�P
	//--------------------------------------------------------------------------------------
	//	class Stage1 : public GameObject;
	//--------------------------------------------------------------------------------------
	class Stage1 : public GameObject
	{
		float m_totalTime;

	public:
		// �\�z�Ɣj��
		Stage1(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Stage1()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};


	//�X�e�[�W�Q
	//--------------------------------------------------------------------------------------
	//	class Stage2 : public GameObject;
	//--------------------------------------------------------------------------------------
	class Stage2 : public GameObject
	{
		float m_totalTime;

	public:
		// �\�z�Ɣj��
		Stage2(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Stage2()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};



	//�X�e�[�W�R
	//--------------------------------------------------------------------------------------
	//	class Stage3 : public GameObject;
	//--------------------------------------------------------------------------------------
	class Stage3 : public GameObject
	{
		float m_totalTime;

	public:
		// �\�z�Ɣj��
		Stage3(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Stage3()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};


}
//end basecross
