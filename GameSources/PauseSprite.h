/*!
@file pauseSprite.h
@brief タイトル名など
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class pauseSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class pauseSprite : public GameObject
	{
	public:
		// 構築と破棄
		pauseSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~pauseSprite()
		{
		}

		virtual void OnCreate() override; // 初期化
		//virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
