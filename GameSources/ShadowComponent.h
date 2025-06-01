#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowStrategy.h"

namespace basecross
{
    class ShadowComponent : public GameObject
    {
    private:
        std::vector<Vec3> shadowVertices;  // 影の頂点
        std::shared_ptr<ShadowStrategy> shadowStrategy; // 影の計算方式（ストラテジー）
        std::shared_ptr<PCStaticDraw> m_drawComp; // 描画コンポーネント
        void CreatePolygonMesh(); // 影のメッシュを作成

    public:

        ShadowComponent(std::shared_ptr<Stage> stage, std::shared_ptr<ShadowStrategy> strategy)
            : GameObject(stage), shadowStrategy(strategy) // 修正
        {
        }

        virtual ~ShadowComponent() {} // デストラクタを追加
        
        void ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& objectVertices);
        const std::vector<Vec3>& GetShadowVertices() const { return shadowVertices; }
        void SetShadowVertices(const std::vector<Vec3>& vertices) { shadowVertices = vertices; }
        void RenderShadow();

        void OnCreate() override;
    };
}