
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
		ptrColl->SetFixed(true);
		//�^�O������
		AddTag(L"Goal");

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto shadowPtr = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		shadowPtr->SetMeshResource(L"DEFAULT_CUBE");

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);


	}

	void goalGate::OnUpdate()
	{
		auto ptrColl = GetComponent<CollisionObb>();
		if (!ptrColl) return; // �Փ˔���R���|�[�l���g���Ȃ��ꍇ�͏������I��

		//auto player = GetStage()->FindObjectByTag(L"Player"); // "Player"�^�O�����I�u�W�F�N�g���擾
		//if (!player) return; // �v���C���[��������Ȃ��ꍇ�͏������I��

		//if (ptrColl->IsColliding(player)) // �v���C���[��goalGate���Փ˂������`�F�b�N
		//{
		//	auto playerObj = dynamic_pointer_cast<Player>(player);//Player�I�u�W�F�N�g�Ƃ��ăL���X�g
		//	if (playerObj && playerObj->hasCheese()) // �v���C���[���`�[�Y�������Ă���ꍇ
		//	{
		//		gameClear(); // �Q�[���N���A���������s
		//	}
		//}
	}
}
//end basecross
