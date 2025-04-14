
/*!
@file Box.h
@brief 箱オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Box : public GameObject
	{
	public:
		//コンストラクタ
		Box(const shared_ptr<Stage>& stage) :
			GameObject(stage)

		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

}
//end basecross
#pragma once

