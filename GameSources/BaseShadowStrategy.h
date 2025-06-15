#pragma once
#include"stdafx.h"
#include"Project.h"

namespace basecross
{
	class BaseShadowStrategy :public GameObject
	{
	public:
		BaseShadowStrategy(const shared_ptr<Stage>& StagePtr);
		virtual ~BaseShadowStrategy(){}
		virtual Vec3 Cross(const Vec3& v1, const Vec3& v2) const;
		virtual std::vector<Vec3> Sort(std::vector<Vec3> vertices);
		virtual std::vector<Vec3> ComputeConvexHull(std::vector<Vec3> vertices) = 0;
		virtual std::vector<Vec3> ComputeShadow(const Vec3& lightPos, const std::shared_ptr<GameObject>& obj) = 0;
	};
}