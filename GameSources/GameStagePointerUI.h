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

		float m_totalTime;


	public:
		// 構築と破棄
		GameStagePointerUI(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_totalTime(0.0f)
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

		//操作可能Boxのポインター
		void SetTargetBox(const shared_ptr<Box>& target);
		//選択中Boxのポインター
		void SetBlingBox(const shared_ptr<Box>& target);

	};
}
//end basecross
