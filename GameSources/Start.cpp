
/*!
@file Character.cpp
@brief �X�^�[�g�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//�\�z�Ɣj��
	startGate::startGate(const shared_ptr<Stage>& StagePtr,
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
	startGate::~startGate() {}

	//������
	void startGate::OnCreate()
	{
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//OBB�Փ�j�����t����
		/*auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);*/
		//�^�O������
		//AddTag(L"startGate");

		//�e������i�V���h�E�}�b�v��`�悷��j
		//auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"TEX_CHEESE");

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);


	}
}
//end basecross
