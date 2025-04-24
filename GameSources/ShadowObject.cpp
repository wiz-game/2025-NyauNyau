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
		static float rotate = 0.0f;

		auto light = GetStage()->GetSharedGameObject<SpotLight>(L"SpotLight"); //���C�g���擾
		m_lightPos = light->GetComponent<Transform>()->GetPosition();

		auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
		Vec3 wallNormal = wall->GetWallNormal();
		Vec3 wallPoint = wall->GetWallPosition();
		
		Mat4x4 matrix;
		matrix.affineTransformation(Vec3(1), Vec3(0), Vec3(rotate, rotate, rotate), Vec3(0)); // �g��E��]�s����쐬
		auto wallPointVec  = XMVectorSet(wallPoint.x+0.001, wallPoint.y, wallPoint.z, 0.0f);//DirectX��Vecter�ɕϊ�
		auto wallNormalVec = XMVectorSet(wallNormal.x, wallNormal.y, wallNormal.z, 0.0f);//DirectX��Vecter�ɕϊ�
		//auto light = XMVectorSet(-4.0f, 0.0f, 0.0f, 0.0f); // �e���f�����C�g�̑z��ʒu
		//auto wallPointVec = XMVectorSet (-5.299f, 4.0f, 0.0f, 0.0f);//DirectX��Vecter�ɕϊ�
		//auto wallNormalVec = XMVectorSet(-1.0f,0.0f, 0.0f, 0.0f);//DirectX��Vecter�ɕϊ�
		//auto plane = XMPlaneFromPointNormal(wallPointVec, wallNormalVec); // ���ʏ��1�_�ƁA���̕��ʂ̌�������u���ʁv�����
		auto plane = XMPlaneFromPointNormal(wallPointVec, wallNormal);
		auto shadowMatrix = XMMatrixShadow(plane, m_lightPos*-1); // �ˉe�s����쐬
		Mat4x4 shadowMat4x4(shadowMatrix); // BaseCross�̍s��(Mat4x4)�ɕϊ�

		

		// �h���[�R���|�[�l���g�ɍs���K�p����
		m_drawComp->SetMeshToTransformMatrix(matrix * shadowMat4x4);

		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(XMVectorGetX(wallNormalVec), 6, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Y=" + Util::FloatToWStr(XMVectorGetY(wallNormalVec), 6, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Z=" + Util::FloatToWStr(XMVectorGetZ(wallNormalVec), 6, Util::FloatModify::Fixed) + L"\n";


		wstring str = positionStr;


		//������R���|�[�l���g�̎擾
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}
}