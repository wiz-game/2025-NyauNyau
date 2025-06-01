#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowStrategy.h"

namespace basecross
{
    class ShadowComponent : public GameObject
    {
    private:
        std::vector<Vec3> shadowVertices;  // �e�̒��_
        std::shared_ptr<ShadowStrategy> shadowStrategy; // �e�̌v�Z�����i�X�g���e�W�[�j
        std::shared_ptr<PCStaticDraw> m_drawComp; // �`��R���|�[�l���g
        void CreatePolygonMesh(); // �e�̃��b�V�����쐬

    public:

        ShadowComponent(std::shared_ptr<Stage> stage, std::shared_ptr<ShadowStrategy> strategy)
            : GameObject(stage), shadowStrategy(strategy) // �C��
        {
        }

        virtual ~ShadowComponent() {} // �f�X�g���N�^��ǉ�
        
        void ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& objectVertices);
        const std::vector<Vec3>& GetShadowVertices() const { return shadowVertices; }
        void SetShadowVertices(const std::vector<Vec3>& vertices) { shadowVertices = vertices; }
        void RenderShadow();

        void OnCreate() override;
    };
}