/*!
@file BackgroundTitleSprite.h
@brief タイトル名など
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class BackgroundTitleSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class BackgroundTitleSprite : public GameObject
	{

	public:
		// 構築と破棄
		BackgroundTitleSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		virtual ~BackgroundTitleSprite()
		{
		}


		virtual void OnCreate() override; // 初期化
		//virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
