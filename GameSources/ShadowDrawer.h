#pragma once
#include "stdafx.h"
#include "Project.h"

//オブジェクトに直接コンポーネントすると座標がオブジェクトと加算されてしまって
//描画が変になるのでこのスクリプトにAddComponentしてこのスクリプトを
//GameStageにAddGameObjectして正しい座標で影を描画させる

namespace basecross {
    class ShadowDrawer : public GameObject {
    public:
        ShadowDrawer(const std::shared_ptr<Stage>& stage);
        void OnCreate() override;
    };
}