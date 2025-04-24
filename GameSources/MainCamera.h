#pragma once
/*!
@file MainCamera.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	class MainCamera : public Camera;
	//--------------------------------------------------------------------------------------
	class MainCamera : public Camera
	{
		// 注視対象オブジェクト
		std::weak_ptr<GameObject> m_targetObj;

		float m_height; // カメラの高さ
		float m_distance; // 注視点空の距離
		float m_angleY; // Y軸中心のカメラの回り込み

	public:
		// 構築と破棄
		MainCamera(const shared_ptr<Stage>& stage) :
			m_height(4.5f),
			m_distance(4.0f),
			m_angleY(-XM_PIDIV2) // 「π/2」ラジアン→「90°」
		{
		}

		virtual ~MainCamera()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新

		// 注視対象を設定する関数
		void SetTargetObject(const shared_ptr<GameObject>& object)
		{
			m_targetObj = object;
		}
	};

}
//end basecross
