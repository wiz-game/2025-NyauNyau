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
		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;
		std::vector<VertexPositionColorTexture> m_vertices;


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
		
		void SetColor(const Col4& color);
		void SetColor(float r, float g, float b, float a);


	};



}
//end basecross
