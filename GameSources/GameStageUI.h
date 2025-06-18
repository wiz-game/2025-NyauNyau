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

		std::weak_ptr<Box> m_targetBox;

		bool m_isTracking = false;

		Vec3 m_worldOffset = Vec3(0.0f, 2.0f, 0.0f); // ブロックの頭上をターゲットに


	public:
		// 構築と破棄
		GameStageUI(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~GameStageUI()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
		
		
		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);
		
		void SetColor(const Col4& color);
		void SetColor(float r, float g, float b, float a);

		bool GetPointer()
		{
			return m_isTracking;
		}

		void SetPointer(bool p)
		{
			m_isTracking = p;
		}

		void SetTargetBox(const shared_ptr<Box>& target);


		bool GameStageUI::ProjectWorldToScreen(const Vec3& worldPos,
			const shared_ptr<Camera>& camera,
			const basecross::Viewport& viewport,
			Vec2& outScreenPos);// 結果を引数で受け取る
	};
}
//end basecross
