/*!
@file BackTitleButton.h
@brief �X�^�[�g�{�^�� �X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class BackTitleButton : public GameObject;
	//--------------------------------------------------------------------------------------

	class BackTitleButton2 : public GameObject
	{
		float m_totalTime;
		float blinkSpeed = 3;//�_�ő��x
		std::vector<VertexPositionColorTexture> m_vertices;

	public:
		// �\�z�Ɣj��
		BackTitleButton2(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~BackTitleButton2()
		{
		}

		virtual void OnCreate() override; // ������
		virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
	};
}
