/*!
@file GameOverSprite.h
@brief ゲームオーバースプライトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class GameOverSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class GameOverSprite : public GameObject
	{
		//元の座標を保存しておく変数
		Vec3 m_originalPosition;
		//揺れているかどうかのフラグ
		bool m_isShaking;
		//揺れを持続する時間
		float m_shakeDuration;
		//揺れの強さ
		float m_shakePower;


	public:
		// 構築と破棄
		GameOverSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_isShaking(false),
			m_shakeDuration(0.0f),
			m_shakePower(5.0f)
		{
		}

		virtual ~GameOverSprite()
		{
		}


		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画

		void StartShake(float duration, float power = 5.0f);
	};

}
//end basecross
