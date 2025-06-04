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

	public:
		// 構築と破棄
		GameOverSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		virtual ~GameOverSprite()
		{
		}


		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};

}
//end basecross
