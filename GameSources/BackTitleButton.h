/*!
@file BackTitleButton.h
@brief スタートボタン スプライトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class BackTitleButton : public GameObject;
	//--------------------------------------------------------------------------------------
	class BackTitleButton : public GameObject
	{
		float m_totalTime;
		float blinkSpeed;//点滅速度
		std::vector<VertexPositionColorTexture> m_vertices;
		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;

		bool m_Select;

	public:
		// 構築と破棄
		BackTitleButton(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			blinkSpeed(3.0f),
			m_Select(false)
		{
		}
		virtual ~BackTitleButton()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画

		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);


		//スプライトナンバーのアクセサ
		int GetSelected() const
		{
			return m_Select;
		}

		void SetSelected(int i)
		{
			m_Select = i;
		}

	};

}
//end basecross
