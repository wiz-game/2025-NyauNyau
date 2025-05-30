#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowComponent.h"

namespace basecross
{
    void ShadowComponent::ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& objectVertices)
    {
        if (shadowStrategy)
        {
            shadowVertices = shadowStrategy->ComputeShadow(lightPos, objectVertices);
        }
    }

    void ShadowComponent::RenderShadow(const std::vector<Vec3>& vertices)
    {
        for (const auto& vertex : vertices)
        {
            std::cout << "Shadow Vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;
        }
    }
}