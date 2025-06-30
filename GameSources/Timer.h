#pragma once
#include "stdafx.h"

namespace basecross
{
	class Timer : public GameObject
	{
		Timer(const shared_ptr<Stage>& StagePtr
		);
	public:
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}