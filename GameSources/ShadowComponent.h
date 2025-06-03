#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowStrategy.h"

namespace basecross
{
    class ShadowComponent : public GameObject
    {
    private:
        Vec3 m_lightPos;  // 光源の位置
        std::vector<Vec3> shadowVerticesCurrent;  // 現在フレームの影ポリゴン
        std::vector<Vec3> shadowVerticesPrevious; // 前フレームの影ポリゴン
        bool usePreviousBuffer = false; // ダブルバッファの切り替え

        std::shared_ptr<ShadowStrategy> shadowStrategy;
        std::shared_ptr<PCStaticDraw> m_drawComp; // 描画コンポーネント

    public:
        ShadowComponent(std::shared_ptr<ShadowStrategy> strategy);

        void OnUpdate() override;  // 毎フレーム光源を取得 & 影を計算
        void ComputeShadow();
        void RenderShadow();
        void SwapBuffers(); // バッファ切り替え
    };
}