/*!
@file Sprite.h
@brief タイトル名など
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class Sprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class Sprite : public GameObject
	{
	public:
		// 構築と破棄
		Sprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Sprite()
		{
		}

		virtual void OnCreate() override; // 初期化
		//virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
