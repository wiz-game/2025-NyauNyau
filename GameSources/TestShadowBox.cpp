#include "stdafx.h"
#include "Project.h"


namespace basecross
{
	//�\�z�Ɣj��
	TestShadowBox::TestShadowBox(const shared_ptr<Stage>& StagePtr,
		 Vec3& Scale,
		 Vec3& Rotation,
		 Vec3& Position

	):

		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)

	{}


	void TestShadowBox::OnCreate()
	{
		// �h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // �L���[�u�^�̃��b�V����ݒ肷��
		//drawComp->SetOwnShadowActive(true); // �e���󂯓����
		//drawComp->SetTextureResource(L"TEX_YUKA");

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionRect>();
		ptrColl->SetFixed(true);

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


	}

	void TestShadowBox::OnUpdate()
	{
	}



}