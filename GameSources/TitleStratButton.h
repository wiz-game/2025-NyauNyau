/*!
@file TitleStartButton.h
@brief �X�^�[�g�{�^�� �X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class TitleStartButton : public GameObject;
	//--------------------------------------------------------------------------------------
	class TitleStartButton : public GameObject
	{
		float m_totalTime;
		float blinkSpeed = 3;//�_�ő��x
		std::vector<VertexPositionColorTexture> m_vertices;

	public:
		// �\�z�Ɣj��
		TitleStartButton(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~TitleStartButton()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};




	class TitleStartButton2 : public GameObject
	{
		float m_totalTime;
		float blinkSpeed = 3;//�_�ő��x
		std::vector<VertexPositionColorTexture> m_vertices;

	public:
		// �\�z�Ɣj��
		TitleStartButton2(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~TitleStartButton2()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};

}
//end basecross
