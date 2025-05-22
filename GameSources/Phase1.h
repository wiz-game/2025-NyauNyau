#pragma once
#include "stdafx.h"

namespace basecross
{

	class Phase1: public GameObject
	{
	public:
		// \’z‚Æ”jŠü
		Phase1(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Phase1()
		{
		}

		virtual void OnCreate() override; // ‰Šú‰»
		virtual void OnUpdate() override; // XV
		//virtual void OnDraw() override; // •`‰æ
	};



}