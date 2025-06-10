#include "stdafx.h"
#include "Project.h"
#include "Components.h"
#include "ShadowComponent.h"

namespace basecross
{

    ShadowComponent::ShadowComponent(const std::shared_ptr<GameObject>& owner, const std::shared_ptr<BoxShadowStrategy>& strategy)
        : Component(owner), boxShadowStrategy(strategy)
    {
    }

    void ShadowComponent::OnDraw()
    {
       
    }

    void ShadowComponent::OnCreate()
    {
        m_drawComp = GetGameObject()->AddComponent<PCStaticDraw>();
        m_drawComp->SetOriginalMeshUse(true);

    }

    void ShadowComponent::OnUpdate()
    {
        // 光源の位置を取得
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

        auto box = GetStage()->GetSharedGameObject<Box>(L"Box");
        if (!box) return;

        shadowVerticesCurrent = boxShadowStrategy->ComputeShadow(m_lightPos, box);

    }

    void ShadowComponent::SwapBuffers()
    {
        if (usePreviousBuffer)
        {
            shadowVerticesPrevious = shadowVerticesCurrent; // 前フレームの影を保存
        }

        usePreviousBuffer = !usePreviousBuffer; // 次のフレームで切り替え
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
    

//end basecross
