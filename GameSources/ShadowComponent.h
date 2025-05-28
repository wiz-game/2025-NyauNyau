#pragma once
#include "stdafx.h"  
#include "Project.h"
#include "ShadowStrategy.h"

namespace basecross
{
	class ShadowComponent 
	{
    
        std::vector<Vec3> shadowVertices;  // 影の頂点
        std::shared_ptr<ShadowStrategy> shadowStrategy; // 影の計算方式（ストラテジー）

    public:
        ShadowComponent(std::shared_ptr<ShadowStrategy> strategy) : shadowStrategy(strategy) {}

        void ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& objectVertices);
        std::vector<Vec3> GetShadowVertices() const { return shadowVertices; }
        void SetShadowVertices(const std::vector<Vec3>& vertices) { shadowVertices = vertices; }
        void RenderShadow(const std::vector<Vec3>& vertices); // 影を描画

	};

}