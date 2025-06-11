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
        Vec3 m_lightPos;  // �����̈ʒu
        std::vector<Vec3> shadowVerticesCurrent;  // ���݃t���[���̉e�|���S��
        std::vector<Vec3> shadowVerticesPrevious; // �O�t���[���̉e�|���S��
        bool usePreviousBuffer = false; // �_�u���o�b�t�@�̐؂�ւ�

        std::shared_ptr<BoxShadowStrategy> boxShadowStrategy;
        std::shared_ptr<PCStaticDraw> m_drawComp; // �`��R���|�[�l���g

    public:
        // �X�g���e�W�i�e�̌v�Z���@���`�j
        std::shared_ptr<BoxShadowStrategy> m_ShadowStrategy;

        // �v�Z���ꂽ�e�̒��_���X�g�i���[���h���W�j
        std::vector<Vec3> m_shadowVertices;

        // --- �v���C�x�[�g�ȃw���p�[�֐� ---

        // �e�̃��b�V���f�[�^���X�V����
        void UpdateMesh();

        // �R���X�g���N�^�F�I�[�i�[�ƁA�g�p����X�g���e�W���󂯎��
        ShadowComponent(const std::shared_ptr<GameObject>& owner, const std::shared_ptr<BoxShadowStrategy>& strategy);

        // --- ���C�t�T�C�N�����\�b�h ---

        // �R���|�[�l���g�̏��������ɌĂяo�����
        void OnCreate() override;

        // ���t���[���̍X�V���ɌĂяo�����
        void OnUpdate() override;

        // �`�掞�ɌĂяo�����i����͕`��R���|�[�l���g�ɔC����̂ŋ�j
        void OnDraw() override;
    };


}