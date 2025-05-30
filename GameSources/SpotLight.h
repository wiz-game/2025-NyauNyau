
/*!
@file SpotLight.h
@brief ライトオブジェクトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpotLight : public GameObject
	{
		shared_ptr<PNTStaticModelDraw> m_drawComp;


	public:
		//コンストラクタ
		SpotLight(const shared_ptr<Stage>& stage) :
			GameObject(stage)

		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void InitDrawComp();

	};


}
//end basecross

