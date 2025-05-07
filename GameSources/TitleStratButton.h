/*!
@file TitleStartButton.h
@brief スタートボタン スプライトなど
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
		// 構築と破棄
		TitleStartButton(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~TitleStartButton()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
