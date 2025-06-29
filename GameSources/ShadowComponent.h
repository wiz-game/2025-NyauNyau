#pragma once
#include "stdafx.h"
#include "Project.h"
#include "Components.h"
#include "BoxShadowStrategy.h"

namespace basecross
{
    class ShadowComponent : public Component
    {
    private:
        std::vector<Vec3> shadowVerticesCurrent;  // 現在フレームの影ポリゴン
        std::vector<Vec3> shadowVerticesPrevious; // 前フレームの影ポリゴン
        bool usePreviousBuffer = false; // ダブルバッファの切り替え

        std::shared_ptr<BoxShadowStrategy> boxShadowStrategy;
        std::shared_ptr<PCStaticDraw> m_drawComp; // 描画コンポーネント
       

    public:
        // ストラテジ（影の計算方法を定義）
        std::shared_ptr<BoxShadowStrategy> m_ShadowStrategy;

        // 計算された影の頂点リスト（ワールド座標）
        //std::vector<Vec3> m_shadowVertices;
        void SetStrategy(const std::shared_ptr<BoxShadowStrategy>& strategy);

        std::vector<std::vector<Vec3>> m_allShadowsVertices;  

        // 影のメッシュデータを更新する
        void UpdateMesh();

        // コンストラクタ：オーナーと、使用するストラテジを受け取る
        ShadowComponent(const std::shared_ptr<GameObject>& owner, const std::shared_ptr<BoxShadowStrategy>& strategy);

        //すべとの影の頂点データを渡す
       // 計算済みの、すべての影の頂点リストを返す
        const std::vector<std::vector<Vec3>>& GetAllShadowsVertices() const;
        // --- ライフサイクルメソッド ---

        // コンポーネントの初期化時に呼び出される
        void OnCreate() override;

        // 毎フレームの更新時に呼び出される
        void OnUpdate() override;

        // 描画時に呼び出される（今回は描画コンポーネントに任せるので空）
        void OnDraw() override;
    };


}