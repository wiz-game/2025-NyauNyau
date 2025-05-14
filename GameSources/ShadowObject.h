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
        std::vector<Vec3> m_shadowVertices; //�e�̃|���S�����_  

    public:
        Vec3 m_lightPos; // �����̈ʒu  

        ShadowObject(const shared_ptr<Stage>& stage)
            : GameObject(stage), m_lightPos(0)
        {
        }

        virtual ~ShadowObject() {}

        // Box�̒��_���擾  
        std::vector<Vec3> GetBoxVertices();

        // �����ƃ{�b�N�X�̒��_����Ō��сA���̉�������ǂ܂ŐL�΂���_���擾  
        std::vector<Vec3> ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& boxVertices);

        // �Ǖ��ʂ̕������𐶐�  
        Vec4 GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal);

        //��_�̓ʕ���v�Z  
        std::vector<Vec3> ComputeConvexHull(std::vector<Vec3> vertices);

        //�e�|���S���𐶐�  
        void CreatePolygonMesh(const std::vector<Vec3>& vertices);

        //�x�N�g���̊O�ς��v�Z
        float Cross(const Vec2& a, const Vec2& b, const Vec2& c);

        //�o�u���\�[�g  
        void BubbleSort(std::vector<Vec3>& vertices);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
    };
}