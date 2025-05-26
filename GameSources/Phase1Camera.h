/*!
@file Phse1Camera.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class Phase1Camera : public Camera;
	//--------------------------------------------------------------------------------------
	class Phase1Camera : public Camera
	{
		float m_height; // カメラの高さ
		float m_distance; // 注視点空の距離
		float m_angleY; // Y軸中心のカメラの回り込み

	public:
		// 構築と破棄
		Phase1Camera() :
			m_height(0.0f),
			m_distance(0.0f),
			m_angleY(90.0f) // 「π/2」ラジアン→「90°」
		{
		}

		virtual ~Phase1Camera()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新

	};

}
//end basecross
