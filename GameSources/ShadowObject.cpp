/*!
@file ShadowObject.h
@brief �e�̎Z�o�E�`����s���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"
#include "Project.h"
#include "ShadowObject.h"

namespace basecross
{
	void ShadowObject::OnCreate()
	{
		m_drawComp = AddComponent<PCStaticDraw>();
		m_drawComp->SetMeshResource(L"DEFAULT_CUBE");
		m_drawComp->SetDiffuse(Col4(0, 0, 0, 1));
		m_drawComp->SetEmissive(Col4(0.2, 0.2, 0.2, 1));

		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(32.0f, 32.0f, 640.0f, 480.0f));

	}

    void ShadowObject::OnUpdate()
    {
        static float rotate = 0.0f; // ��]

        // ���C�g�̈ʒu���擾
        auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight");
        Vec3 lightPos = light->GetComponent<Transform>()->GetPosition();

        // �ǂ̏����擾
        auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
        Vec3 wallNormal = wall->GetWallNormal();
        Vec3 wallPoint = wall->GetWallPosition();

        //�I�u�W�F�N�g�̈ʒu���̎擾
        auto boxObj = GetStage()->GetSharedGameObject<Box>(L"Box");
        Vec3 boxObjPos = boxObj->GetComponent<Transform>()->GetPosition();

        // **�e�̔{���𓮓I�Ɍv�Z**
        float shadowScale = CalculateShadowScale(lightPos, boxObjPos, wallPoint, wallNormal);

        // **�I�u�W�F�N�g�̓����ɉ����ĉe�̈ʒu���X�V**
        Vec3 lightDirection = Vec3(boxObjPos - lightPos).normalize();
        float t = ((wallPoint - lightPos).dot(wallNormal)) / (lightDirection.dot(wallNormal));
        Vec3 shadowPosition = lightPos + lightDirection * t;

        // **�e�̍s���K�p**
        Mat4x4 matrix;
        matrix.affineTransformation(Vec3(shadowScale), Vec3(0), Vec3(rotate, rotate, rotate), shadowPosition);

        // �ˉe�s���K�p�i�����Ɖe�̊֌W���l���j
        auto wallPointVec = XMVectorSet(wallPoint.x, wallPoint.y, wallPoint.z, 0.0f);
        auto wallNormalVec = XMVectorSet(wallNormal.x, wallNormal.y, wallNormal.z, 0.0f);
        auto plane = XMPlaneFromPointNormal(wallPointVec, wallNormalVec);
        auto shadowMatrix = XMMatrixShadow(plane, lightPos * -1);

        Mat4x4 shadowMat4x4(shadowMatrix);

        // **�e�̍s����I�u�W�F�N�g�ɓK�p**
        m_drawComp->SetMeshToTransformMatrix(matrix * shadowMat4x4);
    }

    float  ShadowObject::CalculateShadowScale(const Vec3& lightPos, const Vec3& objectPos, const Vec3& wallPoint, const Vec3& wallNormal)
    {
        // �������I�u�W�F�N�g���Ⴂ�ꍇ�A�e�̔{���� 1.0f �ɂ���i�e����������������Ȃ��j
        if (lightPos.y <= objectPos.y) {
            return 1.0f;
        }

        // �����ƃI�u�W�F�N�g�̋������v�Z
        float objectDistance = (objectPos - lightPos).length();

        // �����̕����i���� �� �I�u�W�F�N�g�̕����j
        Vec3 lightDirection = Vec3(objectPos - lightPos).normalize();

        // �ǂƂ̌�_�����߂�i�����̕����ƕǂ̖@����p�����v�Z�j
        float t = ((wallPoint - lightPos).dot(wallNormal)) / (lightDirection.dot(wallNormal));

        // �ǂɓ��e���ꂽ�e�̈ʒu�����߂�
        Vec3 shadowPoint = lightPos + lightDirection * t;

        // �e�̒������v�Z�i�I�u�W�F�N�g����e�̓��e�_�܂Łj
        float shadowLength = Vec3(shadowPoint - objectPos).length();

        // �e�̔{�����v�Z�i�e�̒��� / �����ƃI�u�W�F�N�g�̋����j
        float shadowScale = shadowLength / objectDistance;

        return shadowScale;
    }
}
