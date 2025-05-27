/*!
@file BackTitleButton.h
@brief ステージスプライトなど
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
		// 構築と破棄
		FootprintSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~FootprintSprite()
		{
		}

		virtual void OnCreate() override; // 初期化
		//virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void SetRotate(float x, float y, float z);

	};



}
//end basecross
