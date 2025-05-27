/*!
@file BackTitleButton.h
@brief �X�e�[�W�X�v���C�g�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class FootprintSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class FootprintSprite : public GameObject
	{

		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;


	public:
		// �\�z�Ɣj��
		FootprintSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~FootprintSprite()
		{
		}

		virtual void OnCreate() override; // ������
		//virtual void OnUpdate() override; // �X�V
		//virtual void OnDraw() override; // �`��
		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void SetRotate(float x, float y, float z);

	};



}
//end basecross
