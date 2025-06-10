#include "stdafx.h"
#include "Project.h"
#include "Components.h"
#include "ShadowComponent.h"

namespace basecross
{

    ShadowComponent::ShadowComponent(const std::shared_ptr<GameObject>& owner, const std::shared_ptr<BoxShadowStrategy>& strategy)
        : Component(owner),
        m_ShadowStrategy(strategy), // ストラテジを保持
        m_drawComp(nullptr)            // 描画コンポーネントはnullptrで初期化
    {
    }

    void ShadowComponent::OnCreate()
    {
        // 自分自身が所属するGameObjectに、描画能力を追加する
        m_drawComp = GetGameObject()->AddComponent<PCStaticDraw>();
        m_drawComp->SetOriginalMeshUse(true); // 動的メッシュを使う設定
        m_drawComp->SetRasterizerState(RasterizerState::CullNone);
    }

    void ShadowComponent::OnUpdate()
    {
        // --- 計算処理 ---

        // 光源の位置を取得
        auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        if (!light) return;
        Vec3 lightPos = light->GetComponent<Transform>()->GetPosition();

        // 影を落とすオブジェクトを取得 (将来的にはもっと汎用的な方法で)
        auto box = GetStage()->GetSharedGameObject<Box>(L"Box_0");
        if (!box) return;

        // ストラテジを使って、影の頂点リストを計算
        m_shadowVertices = m_ShadowStrategy->ComputeShadow(lightPos, box);

        // 計算結果を基に、描画用メッシュを更新
        UpdateMesh();
    }

    // OnDrawは描画コンポーネントに任せるので、空でOK
    void ShadowComponent::OnDraw()
    {
    }

    // メッシュを更新するヘルパー関数
    void ShadowComponent::UpdateMesh()
    {
        if (!m_drawComp) return;

        // 描画できる頂点がなければ、メッシュを空にする
        if (m_shadowVertices.size() < 3)
        {
            m_drawComp->SetOriginalMeshUse(false);
            return;
        }

        m_drawComp->SetOriginalMeshUse(true);

        // 頂点データ(VertexPositionColor)のリストを作成
        std::vector<VertexPositionColor> meshVertices;
        Col4 shadowColor(0.0f, 0.0f, 0.0f, 0.5f); // 半透明の黒
        for (const auto& vertex : m_shadowVertices)
        {
            meshVertices.push_back(VertexPositionColor(vertex, shadowColor));
        }

        // インデックスデータのリストを作成 (トライアングルファン形式)
        std::vector<uint16_t> indices;
        for (size_t i = 1; i < m_shadowVertices.size() - 1; ++i)
        {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        // 描画コンポーネントに、新しいメッシュデータを渡す
        m_drawComp->CreateOriginalMesh(meshVertices, indices);
    }
}
    

//end basecross
