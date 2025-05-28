#pragma once
#include "stdafx.h"
#include "Project.h"
#include "BoxShadowStrategy.h"

namespace basecross
{
    std::vector<Vec3> BoxShadowStrategy::ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& vertices)
    {
        std::vector<Vec3> shadowVertices;
        for (const auto& vertex : vertices)
        {
            Vec3 shadowDir = Vec3(vertex - lightPos).normalize();
            Vec3 shadowVertex = vertex + shadowDir * 0.5f; // ‰e‚ðŠg’£
            shadowVertices.push_back(shadowVertex);
        }
        return shadowVertices;
    }
}