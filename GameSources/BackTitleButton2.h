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

	class BackTitleButton2 : public GameObject
	{
		float m_totalTime;
		float blinkSpeed = 3;//点滅速度
		std::vector<VertexPositionColorTexture> m_vertices;

	public:
		// 構築と破棄
		BackTitleButton2(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~BackTitleButton2()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};
}
