#pragma once
#include"stdafx.h"
#include"Project.h"
#include"ShadowComponent.h"
#include"ShadowStrategy.h"


namespace basecross
{
    void ShadowComponent::OnCreate()
    {
        m_drawComp = AddComponent<PCStaticDraw>();
        m_drawComp->SetOriginalMeshUse(true);

        auto traComp = GetComponent<Transform>();
        traComp->SetRotation(Vec3(0.0f, XM_PI / 2, 0.0f));
        traComp->SetPosition(Vec3(0.1f, 0.75f, 0.0f));

    }


    void ShadowComponent::ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& objectVertices)
    {
        shadowVertices = shadowStrategy->ComputeShadow(lightPos, objectVertices);
    }

    void ShadowComponent::RenderShadow()
    {
        

        CreatePolygonMesh();
    }

    void ShadowComponent::CreatePolygonMesh()
    {
        if (shadowVertices.size() < 3)
        {
            return;
        }

        std::vector<VertexPositionColor> meshVertices;
        Col4 shadowColor(0.0f, 0.0f, 0.0f, 0.5f); // îºìßñæÇÃçïêFÇÃâe

        for (const auto& vertex : shadowVertices)
        {
            Vec3 v(vertex.x, vertex.y, vertex.z);
            meshVertices.push_back(VertexPositionColor(v, shadowColor));
        }

        std::vector<uint16_t> indices;
        for (size_t i = 0; i < shadowVertices.size() - 2; ++i)
        {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }

        m_drawComp->CreateOriginalMesh(meshVertices, indices);
    }
}