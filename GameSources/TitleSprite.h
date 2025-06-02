/*!
@file TitleSprite.h
@brief タイトル名など
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class TitleSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject
	{
		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;
		float m_totalTime;

		Vec3 m_basePosition;//基準位置
		float frequency = 2.0f;// 周期

	public:
		float m_phaseOffset = 0.0f;//各スプライト毎に異なる値をセット
		float m_amplitude = 10.0f;  // sin波の幅

		// 構築と破棄
		TitleSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_totalTime(0.0f)
		{
		}

		virtual ~TitleSprite()
		{
		}


		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画

		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);
	};

}
//end basecross
