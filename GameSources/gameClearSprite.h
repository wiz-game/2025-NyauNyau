/*!
@file gameClearSprite.h
@brief ゲームクリア スプライトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class gameClearSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class gameClearSprite : public GameObject
	{
	public:
		// 構築と破棄
		gameClearSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~gameClearSprite()
		{
		}

		virtual void OnCreate() override; // 初期化
		//virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
