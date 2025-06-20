/*!
@file BackTitleButton.h
@brief ステージスプライトなど
*/

#pragma once
#include "stdafx.h"
#include "Box.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class GameStagePointerUI : public GameObject;
	//--------------------------------------------------------------------------------------
	class GameStagePointerUI : public GameObject
	{
		std::shared_ptr<PCTStaticDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;
		std::vector<VertexPositionColorTexture> m_vertices;

		std::weak_ptr<Box> m_targetBox;

		float m_speed;//上下移動のスピード
		float m_moveRange;//移動範囲
		float m_moveDirection;//移動方向
		bool m_isAnimating;//アニメーション中かどうか
		float m_animationTime;//時間
		float m_baseOffsetY;//上下の中心となるY座標のオフセット



	public:
		// 構築と破棄
		GameStagePointerUI(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_speed(2.0f),
			m_moveRange(1.0f),
			m_isAnimating(false),
			m_animationTime(0.0f),
			m_baseOffsetY(3.5f),
			m_moveDirection(-1.0f)
		{
		}
		virtual ~GameStagePointerUI()
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

		//操作可能Boxのポインター(animationなし)と選択中のBoxのポインター(animationあり)
		void SetTargetBox(const shared_ptr<Box>& target, bool isAnimate);

	};
}
//end basecross
