#include "ShadowComponent.h"

namespace basecross
{
    ShadowComponent::ShadowComponent(std::shared_ptr<ShadowStrategy> strategy)
        : shadowStrategy(strategy), m_drawComp(AddComponent<PCStaticDraw>())
    {
        m_drawComp->SetOriginalMeshUse(true);
    }

    void ShadowComponent::OnUpdate()
    {
        // �����̈ʒu���擾
        auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        if (light)
        {
            m_lightPos = light->GetComponent<Transform>()->GetPosition();
        }

        ComputeShadow();
        RenderShadow();
    }

    void ShadowComponent::ComputeShadow()
    {
        // �o�b�t�@��؂�ւ�
        SwapBuffers();

        // �{�b�N�X�̒��_���擾
        auto boxVertices = GetStage()->GetSharedGameObject<Box>(L"Box")->GetComponent<Transform>()->GetBoxVertices();

        // �e���v�Z
        shadowVerticesCurrent = shadowStrategy->ComputeShadow(m_lightPos, boxVertices);
    }

    void ShadowComponent::SwapBuffers()
    {
        if (usePreviousBuffer)
        {
            shadowVerticesPrevious = shadowVerticesCurrent; // �O�t���[���̉e��ۑ�
        }

        usePreviousBuffer = !usePreviousBuffer; // ���̃t���[���Ő؂�ւ�
    }

    void ShadowComponent::RenderShadow()
    {
        const auto& verticesToRender = usePreviousBuffer ? shadowVerticesPrevious : shadowVerticesCurrent;

        if (verticesToRender.size() < 3)
        {
            return;
        }

        std::vector<VertexPositionColor> meshVertices;
        Col4 shadowColor(0.0f, 0.0f, 0.0f, 0.5f);

        for (const auto& vertex : verticesToRender)
        {
            meshVertices.push_back(VertexPositionColor(vertex, shadowColor));
        }

        std::vector<uint16_t> indices;
        for (size_t i = 0; i < verticesToRender.size() - 2; ++i)
        {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }

        m_drawComp->CreateOriginalMesh(meshVertices, indices);
    }
}