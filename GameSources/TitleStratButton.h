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

}
//end basecross
