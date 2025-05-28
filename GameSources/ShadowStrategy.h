#pragma once
#include "stdafx.h"  
#include "Project.h"

namespace basecross
{
	class ShadowStrategy
	{
	public:
		virtual ~ShadowStrategy() = default;
		virtual std::vector<Vec3> ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& vertices) = 0;
	};

}
