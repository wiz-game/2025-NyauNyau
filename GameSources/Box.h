
/*!
@file Box.h
@brief 箱オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Box : public GameObject
	{
		shared_ptr<PNTStaticDraw> m_drawComp;
		shared_ptr<Transform> m_transComp;


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

