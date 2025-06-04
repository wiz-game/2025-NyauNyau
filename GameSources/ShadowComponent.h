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
        Vec3 m_lightPos;  // 光源の位置
        std::vector<Vec3> shadowVerticesCurrent;  // 現在フレームの影ポリゴン
        std::vector<Vec3> shadowVerticesPrevious; // 前フレームの影ポリゴン
        bool usePreviousBuffer = false; // ダブルバッファの切り替え

        std::shared_ptr<BoxShadowStrategy> boxShadowStrategy;
        std::shared_ptr<PCStaticDraw> m_drawComp; // 描画コンポーネント

    public:
        ShadowComponent(const std::shared_ptr<GameObject>& owner, const std::shared_ptr<BoxShadowStrategy>& strategy);

        void OnDraw() override;
        void OnUpdate();  // 毎フレーム光源を取得 & 影を計算
        void ComputeShadow();
        void RenderShadow();
        void SwapBuffers(); // バッファ切り替え


    };
}