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
        auto lightObj = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        Mat4x4 lightWorldMatrix = lightObj->GetComponent<Transform>()->GetWorldMatrix();
        // x,y,zををワールド座標への変換行列
        Vec3 lightPos = Vec3(lightWorldMatrix._41, lightWorldMatrix._42, lightWorldMatrix._43);

        m_allShadowsVertices.clear();

        auto& allGameObjects = GetStage()->GetGameObjectVec();
        for (auto& gameObj : allGameObjects)
        {
            // それがBoxクラスのオブジェクトか？
            auto box = std::dynamic_pointer_cast<Box>(gameObj);
            if (box) // Boxだったら...
            {
                // そのBoxの影を計算
                std::vector<Vec3> singleShadow = m_ShadowStrategy->ComputeShadow(lightPos, box);
                // 計算結果を、このフレームの影リストに追加
                m_allShadowsVertices.push_back(singleShadow);
            }
        }
        // 影を落とすオブジェクトを取得 (将来的にはもっと汎用的な方法で)
        //auto box = GetStage()->GetSharedGameObject<Box>(L"Box_0");
        //if (!box) return;

        //// ストラテジを使って、影の頂点リストを計算
        //m_shadowVertices = m_ShadowStrategy->ComputeShadow(lightPos, box);


        //auto ownerObject = GetGameObject();
        //if (!ownerObject) return;

        // 計算結果を基に、描画用メッシュを更新
        UpdateMesh();
    }

    // メッシュを更新するヘルパー関数
    void ShadowComponent::UpdateMesh()
    {
        if (!m_drawComp) return;

        // --- 複数の影ポリゴンを、一つの巨大なメッシュにまとめる ---
        std::vector<VertexPositionColor> finalMeshVertices;
        std::vector<uint16_t> finalMeshIndices;
        Col4 shadowColor(0.0f, 0.0f, 0.0f, 0.5f);

        // すべての影ポリゴン（m_allShadowsVertices）をループ
        for (const auto& singleShadowVertices : m_allShadowsVertices)
        {
            if (singleShadowVertices.size() < 3) {
                continue; // この影は描画できないのでスキップ
            }

            // 現在のメッシュの頂点数を、インデックスの「開始番号」として記録
            uint16_t indexOffset = static_cast<uint16_t>(finalMeshVertices.size());

            // 頂点を、最終的なメッシュリストに追加
            for (const auto& vertex : singleShadowVertices)
            {
                finalMeshVertices.push_back(VertexPositionColor(vertex, shadowColor));
            }

            // インデックスを、オフセットを考慮して追加
            for (size_t i = 1; i < singleShadowVertices.size() - 1; ++i)
            {
                finalMeshIndices.push_back(indexOffset + 0);
                finalMeshIndices.push_back(indexOffset + i);
                finalMeshIndices.push_back(indexOffset + i + 1);
            }
        }

        // 描画コンポーネントに、新しいメッシュデータを渡す
        m_drawComp->CreateOriginalMesh(finalMeshVertices, finalMeshIndices);

    }

    void ShadowComponent::SetStrategy(const std::shared_ptr<BoxShadowStrategy>& strategy)
    {
        // 引数で受け取ったストラテジのポインタを、
        // 自分自身のメンバー変数 m_boxShadowStrategy に保存する
        this->m_ShadowStrategy = strategy;
    }


    // オーバーライドしないとエラーが起きるので仮にも定義
    void ShadowComponent::OnDraw()
    {
    }
}