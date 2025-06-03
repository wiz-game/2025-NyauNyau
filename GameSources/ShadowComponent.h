#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowStrategy.h"

namespace basecross
{
    class ShadowComponent : public GameObject
    {
    private:
        Vec3 m_lightPos;  // �����̈ʒu
        std::vector<Vec3> shadowVerticesCurrent;  // ���݃t���[���̉e�|���S��
        std::vector<Vec3> shadowVerticesPrevious; // �O�t���[���̉e�|���S��
        bool usePreviousBuffer = false; // �_�u���o�b�t�@�̐؂�ւ�

        std::shared_ptr<ShadowStrategy> shadowStrategy;
        std::shared_ptr<PCStaticDraw> m_drawComp; // �`��R���|�[�l���g

    public:
        ShadowComponent(std::shared_ptr<ShadowStrategy> strategy);

        void OnUpdate() override;  // ���t���[���������擾 & �e���v�Z
        void ComputeShadow();
        void RenderShadow();
        void SwapBuffers(); // �o�b�t�@�؂�ւ�
    };
}