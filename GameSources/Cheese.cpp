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
		m_Position(Position),
		isTarget(false),
		followDistance(0.5f)
	{
	}
	Cheese::~Cheese() {}


	void Cheese::OnCreate()
	{
		//�h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();		
		//ptrDraw->SetRasterizerState(RasterizerState::Wireframe);
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->SetTextureResource(L"TEX_CHEESE");
		SetAlphaActive(true);
		

		//�g�����X�t�H�[���R���|�[�l���g�̎擾�Ɛݒ�
		m_transComp = GetComponent<Transform>();
		m_transComp->SetPosition(m_Position);
		m_transComp->SetRotation(m_Rotation);
		m_transComp->SetScale(m_Scale);
		//�^�O
		AddTag(L"Cheese");


	}

	void Cheese::OnUpdate()
	{
		//Player�^�O�̎擾
		auto playerSh = GetStage()->GetSharedGameObject<Player>(L"Player_0");
		Vec3 playerPos = playerSh->GetComponent<Transform>()->GetPosition();
		
		//�v���C���[�̐i�s�����̎擾
		Vec3 playerForward = playerSh->GetComponent<Transform>()->GetForward();

		Vec3 cheesePos = m_transComp->GetPosition();
		Vec3 targetPos = playerPos - (playerForward * followDistance);

		//Player��Cheese�̓�_�Ԃ̋����v�Z
		auto len = length(playerPos - cheesePos);

		//�ǔ�����
		if (len < 0.3f) {

			isTarget = true;
		}
		//�ǔ����Ȃ�v���C���[�̌���ֈړ�
		if (isTarget)
		{
			//�v���C���[�̌���Ɉʒu��ݒ�
			Vec3 direction = Vec3(targetPos - cheesePos).normalize();
			Vec3 m_Scale(Vec3(0.25f));

			//��苗����ۂ��A���炩�Ɉړ�
			if (length(targetPos - cheesePos) > 0.1f)
			{
				m_transComp->SetPosition(cheesePos + direction * 0.1);
			}
		}
	}

}
//end basecross
