#include "stdafx.h"
#include "Project.h"
#include "ShadowDrawer.h"
#include "ShadowComponent.h"
#include "BoxShadowStrategy.h"

namespace basecross {
    ShadowDrawer::ShadowDrawer(const std::shared_ptr<Stage>& stage) : GameObject(stage) {}
    void ShadowDrawer::OnCreate() {
        // 自分自身のTransformは、絶対に動かさないように原点に固定する
        GetComponent<Transform>()->SetPosition(0, 0, 0);
        GetComponent<Transform>()->SetRotation(0, 0, 0);
        GetComponent<Transform>()->SetScale(1, 1, 1);

        // このオブジェクトに、影の計算・描画能力を持たせる
        auto stage = GetStage();
        auto shadowStrategy = std::make_shared<BoxShadowStrategy>(stage);
        auto shadowComp = AddComponent<ShadowComponent>(shadowStrategy);
        shadowComp->SetStrategy(shadowStrategy);
    }
}