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
		m_drawComp->SetEmissive(Col4(0.5, 0.5, 0.5, 1));
	}

	void ShadowObject::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();

		auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight"); //���C�g���擾
		m_lightPos = light->GetComponent<Transform>()->GetPosition();

		static float rotate = 0.0f;

		Mat4x4 matrix;
		matrix.affineTransformation(Vec3(1), Vec3(0), Vec3(rotate, rotate, rotate), Vec3(0)); // �g��E��]�s����쐬
		auto wallPoint = XMVectorSet(0.0f, 0.0f, 2.f, 0.0f); // ���ʂ̍��W
		auto wallNormal = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f); // ���ʂ̌���
		auto plane = XMPlaneFromPointNormal(wallPoint, wallNormal); // ���ʏ��1�_�ƁA���̕��ʂ̌�������u���ʁv�����
		auto light = XMVectorSet(0.0f, 0.0f, -3.0f, 1.0f); // �e���f�����C�g�̑z��ʒu
		auto shadowMatrix = XMMatrixShadow(plane, light); // �ˉe�s����쐬
		Mat4x4 shadowMat4x4(shadowMatrix); // BaseCross�̍s��(Mat4x4)�ɕϊ�

		// �h���[�R���|�[�l���g�ɍs���K�p����
		m_drawComp->SetMeshToTransformMatrix(matrix * shadowMat4x4);
	}
}