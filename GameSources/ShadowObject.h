/*!
@file ShadowObject.h
@brief �e�̎Z�o�E�`����s���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
    class ShadowObject : public GameObject
    {
        std::shared_ptr<PCStaticDraw> m_drawComp; // �`��R���|�[�l���g
        std::vector<Vec2> m_shadowVertices; // �e�̃|���S�����_

    public:
        Vec3 m_lightPos; // �����̈ʒu

        ShadowObject(const shared_ptr<Stage>& stage)
            : GameObject(stage), m_lightPos(0)
        {
        }

        virtual ~ShadowObject() {}

        // �e�̔{�������߂�֐�
        //float CalculateShadowScale(const Vec3& lightPos, const Vec3& objectPos, const Vec3& wallPoint, const Vec3& wallNormal);

        // Box�̒��_���擾
        std::vector<Vec3> GetBoxVertices();

        // ��_���v�Z
        //std::vector<Vec3> ComputeShadowIntersections(const Vec4& plane, const Vec3& lightPos, const std::vector<Vec3>& vertices);

        // �e�̃|���S���𐶐��i�ʕ�K�p�j
        //std::vector<Vec2> ComputeConvexHull(const std::vector<Vec2>& vertices);

        // �ǂ̕��ʂ��쐬
        Vec4 GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal);

        // �ʕ�v�Z�p�̊O�ϊ֐�
        float Cross(const Vec2& a, const Vec2& b, const Vec2& c);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
    };
}