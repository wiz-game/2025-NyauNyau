#pragma once
#include "stdafx.h"
#include "Project.h"
#include "BaseShadowStrategy.h"

namespace basecross
{
    class BoxShadowStrategy : public BaseShadowStrategy
    {
    public:
        std::vector<Vec3> ComputeShadow(const Vec3& lightPos, const std::shared_ptr<GameObject>& obj) override;
        std::vector<Vec3> ComputeConvexHull(std::vector<Vec3> vertices) override;
        std::vector<Vec3> ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& objectVertices);
        Vec4 GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal);
    };
}