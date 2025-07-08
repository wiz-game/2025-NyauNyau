/*!
@file BackTitleButton.h
@brief ステージスプライトなど
*/

#pragma once
#include "stdafx.h"
#include "Box.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class GameStageUI : public GameObject;
	//--------------------------------------------------------------------------------------
	class GameStageUI : public GameObject
	{
		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;
		std::vector<VertexPositionColorTexture> m_vertices;

		std::weak_ptr<Player> m_target;

		bool m_isAnimation;
		float m_baseOffsetY;//上下の中心となるY座標のオフセット
		float m_baseOffsetX;//上下の中心となるY座標のオフセット
		float m_totalTime;
		float blinkSpeed;//点滅速度



	public:
		// 構築と破棄
		GameStageUI(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_isAnimation(false),
			m_baseOffsetY(3.5f),
			m_baseOffsetX(3.5f),
			m_totalTime(0.0f),
			blinkSpeed(3.0f)
		{
		}
		virtual ~GameStageUI()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画

		//void OnUpdateUI();
		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);

		void SetColor(const Col4& color);
		void SetColor(float r, float g, float b, float a);


		void SetTargetPlayer(const shared_ptr<Player>& target);
	};
}
//end basecross
