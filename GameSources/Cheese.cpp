/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\�z�Ɣj��
	Cheese::Cheese(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	Cheese::~Cheese() {}


	void Cheese::OnCreate()
	{
		//�h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SQUARE");
		//drawComp->SetTextureResource(L" ");
		drawComp->SetBlendState(BlendState::Additive);//���Z����
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		drawComp->SetDiffuse(Col4(1.0f, 0.0f, 1.0f, 1.0f));//�}�e���A���̊g�U���˂̐F��ݒ�
		drawComp->SetEmissive(Col4(1.0f, 0.0f, 1.0f, 1.0f));

		//�g�����X�t�H�[���R���|�[�l���g�̎擾�Ɛݒ�
		m_transComp = GetComponent<Transform>();
		m_transComp->SetScale(m_Scale);
		m_transComp->SetPosition(m_Position);
		//�^�O
		AddTag(L"Cheese");


	}
	//void Cheese::OnUpdate()
	//{
	//	//�r���{�[�h����
	//	auto stage = GetStage();
	//	auto camera = stage->GetView()->GetTargetCamera();
	//	auto viewAatrix = camera->GetViewMatrix(); //�r���[�s����擾
	//	Quat viewQuat(viewAatrix);//�r���[�s�񂩂�N�H�[�^�j�I��(�l����)���쐬
	//	viewQuat.x *= -1.0f;
	//	viewQuat.y *= -1.0f;
	//	viewQuat.z *= -1.0f;
	//	m_transComp->SetQuaternion(viewQuat);
	//}


}
//end basecross
