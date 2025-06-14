/*!
@file PauseSprite.h
@brief タイトル名など
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class PauseSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class PauseSprite : public GameObject
	{
	public:
		float m_totalTime;//トータル時間
		bool m_Selected;//選択しているかどうか


		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;

		// 構築と破棄
		PauseSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_totalTime(0.0f),
			m_Selected(true)
		{
		}
		virtual ~PauseSprite()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画

		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);

		//m_Selectedのアクセサ
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
