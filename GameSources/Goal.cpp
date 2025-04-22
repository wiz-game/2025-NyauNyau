
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
		m_Position(Position),
		m_gameClear(std::make_shared<bool>(false))//�N���A�������ǂ����i�����l:false�j
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
		ptrColl->SetFixed(true);//�ʒu�Œ�

		if (!ptrColl) return; // �Փ˔���R���|�[�l���g���Ȃ��ꍇ�͏������I��

		auto playerSh = GetStage()->GetSharedGameObject<Player>(L"Player"); // "Player"�^�O���擾
		//Vec3 playerPos = playerSh->GetComponent<Transform>()->GetPosition();//Player�̈ʒu

		if (!ptrColl->IsExcludeCollisionObject(playerSh))//�Փ˔���
		{
			//if (playerSh && playerSh->hasCheese()) // �v���C���[���`�[�Y�������Ă���ꍇ
			//{
				m_gameClear = true; // �Q�[���N���A
			//}
		}
	}
}
//end basecross
