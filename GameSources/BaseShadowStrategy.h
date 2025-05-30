#pragma once
#include"stdafx.h"
#include"Project.h"
#include"ShadowStrategy.h"

namespace basecross
{
	class BaseShadowStrategy :public ShadowStrategy
	{
	protected:
		Vec3 Cross(const Vec3& x, const Vec3& y, const Vec3& z);
		void BubbleSort(std::vector<Vec3>& vertices);
		virtual std::vector<Vec3> ComputeConvexHull(std::vector<Vec3> vertices) = 0;
	};


}