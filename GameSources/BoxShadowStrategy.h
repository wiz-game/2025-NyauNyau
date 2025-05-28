#pragma once
#include "stdafx.h"  
#include "Project.h"
#include "ShadowStrategy.h"

namespace basecross
{
	class BoxShadowStrategy : public ShadowStrategy
	{
	public:
		std::vector<Vec3> ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& vertices) override;
	};

}
