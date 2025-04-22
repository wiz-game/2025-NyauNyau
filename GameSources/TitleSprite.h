/*!
@file TitleSprite.h
@brief タイトル名など
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class TitleSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject
	{
	public:
		// 構築と破棄
		TitleSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~TitleSprite()
		{
		}

		virtual void OnCreate() override; // 初期化
		//virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
