#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowStrategy.h"

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
        /*ShadowComponent::ShadowComponent(const shared_ptr<Stage>& stage)
            : GameObject(stage), 
            m_drawComp(AddComponent<PCStaticDraw>())
        {
        }*/

        void OnCreate() override;
        void OnUpdate() override;  // 毎フレーム光源を取得 & 影を計算
        void ComputeShadow();
        void RenderShadow();
        void SwapBuffers(); // バッファ切り替え


    };
}