#include "stdafx.h"
#include "Project.h"
#include "Components.h"
#include "ShadowComponent.h"

namespace basecross
{

    ShadowComponent::ShadowComponent(const std::shared_ptr<GameObject>& owner, const std::shared_ptr<BoxShadowStrategy>& strategy)
        : Component(owner),
        m_ShadowStrategy(strategy), // �X�g���e�W��ێ�
        m_drawComp(nullptr)            // �`��R���|�[�l���g��nullptr�ŏ�����
    {
    }

    void ShadowComponent::OnCreate()
    {
        // �������g����������GameObject�ɁA�`��\�͂�ǉ�����
        m_drawComp = GetGameObject()->AddComponent<PCStaticDraw>();
        m_drawComp->SetOriginalMeshUse(true); // ���I���b�V�����g���ݒ�
        m_drawComp->SetRasterizerState(RasterizerState::CullNone);


    }
    void ShadowComponent::OnUpdate()
    {
        // --- �v�Z���� ---

        // �����̈ʒu���擾
        auto lightObj = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        Mat4x4 lightWorldMatrix = lightObj->GetComponent<Transform>()->GetWorldMatrix();
        // x,y,z�������[���h���W�ւ̕ϊ��s��
        Vec3 lightBasePos = Vec3(lightWorldMatrix._41, lightWorldMatrix._42, lightWorldMatrix._43);

        // Y���W�̃I�t�Z�b�g��������
        Vec3 lightPos = lightBasePos + Vec3(0.0f, 0.8f, 0.0f);

        // �e�𗎂Ƃ��I�u�W�F�N�g���擾 (�����I�ɂ͂����Ɣėp�I�ȕ��@��)
        auto box = GetStage()->GetSharedGameObject<Box>(L"Box");
        if (!box) return;

        // �X�g���e�W���g���āA�e�̒��_���X�g���v�Z
        m_shadowVertices = m_ShadowStrategy->ComputeShadow(lightPos, box);


        auto ownerObject = GetGameObject();
        if (!ownerObject) return;

        // �v�Z���ʂ���ɁA�`��p���b�V�����X�V
        UpdateMesh();
    }

    // ���b�V�����X�V����w���p�[�֐�
    void ShadowComponent::UpdateMesh()
    {
        if (!m_drawComp) return;

        // �`��ł��钸�_���Ȃ���΁A���b�V������ɂ���
        if (m_shadowVertices.size() < 3)
        {
            m_drawComp->SetOriginalMeshUse(false);
            return;
        }

        m_drawComp->SetOriginalMeshUse(true);

        // ���_�f�[�^(VertexPositionColor)�̃��X�g���쐬
        std::vector<VertexPositionColor> meshVertices;
        Col4 shadowColor(0.0f, 0.0f, 0.0f, 0.5f); // �������̍�
        for (const auto& vertex : m_shadowVertices)
        {
            meshVertices.push_back(VertexPositionColor(vertex, shadowColor));
        }

        // �C���f�b�N�X�f�[�^�̃��X�g���쐬 (�g���C�A���O���t�@���`��)
        std::vector<uint16_t> indices;
        for (size_t i = 1; i < m_shadowVertices.size() - 1; ++i)
        {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }

        // �`��R���|�[�l���g�ɁA�V�������b�V���f�[�^��n��
        m_drawComp->CreateOriginalMesh(meshVertices, indices);

    }
    // �I�[�o�[���C�h���Ȃ��ƃG���[���N����̂ŉ��ɂ���`
    void ShadowComponent::OnDraw()
    {
    }
}
    

//end basecross
