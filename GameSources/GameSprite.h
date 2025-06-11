/*!
@file BackTitleButton.h
@brief ステージスプライトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class GameSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class GameSprite : public GameObject
	{
		//トータル時間
		float m_totalTime;
		float m_speed = 50;//速度

		bool m_isMoving = false;
		float m_moveDirection = 1.0f;//移動方向（1.0：右　-1.0：左）
		float m_moveRange = 15.0f;//移動範囲

		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;


	public:
		// 構築と破棄
		GameSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~GameSprite()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);


		void SetMovementActive(bool IsActive)
		{
			m_isMoving = IsActive;
		}
	};



}
//end basecross
