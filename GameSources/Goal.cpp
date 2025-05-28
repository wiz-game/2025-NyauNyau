
/*!
@file Character.cpp
@brief �S�[���̎���
*/

#include "stdafx.h"
#include "Project.h"
namespace basecross
{
	//�\�z�Ɣj��
	goalGate::goalGate(const shared_ptr<Stage>& StagePtr,
		Vec3& Scale,
		Vec3& Rotation,
		Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	goalGate::~goalGate() {}

	//������
	void goalGate::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(false);
		//�^�O������
		AddTag(L"Goal");

		////�e������i�V���h�E�}�b�v��`�悷��j
		//auto shadowPtr = AddComponent<Shadowmap>();
		////�e�̌`�i���b�V���j��ݒ�
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		ptrDraw->SetTextureResource(L"TEX_SHELF");

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);


	}

	void goalGate::OnUpdate()
	{

	}

	void goalGate::OnCollisionEnter(shared_ptr<GameObject>& collision)
	{
		if (dynamic_pointer_cast <Player>(collision))
		{
			auto& app = App::GetApp();
			PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToGoalStage");

		}
	}

}
//end basecross
