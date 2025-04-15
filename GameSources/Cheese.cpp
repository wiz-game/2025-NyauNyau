/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\�z�Ɣj��
	Cheese::Cheese(const shared_ptr<Stage>& StagePtr
		//const Vec3& Scale,
		//const Vec3& Rotation,
		//const Vec3& Position
	) :
		GameObject(StagePtr),
		//m_Scale(Scale),
		//m_Rotation(Rotation),
		//m_Position(Position),
		direction(2.0f)
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
		m_transComp->SetPosition(Vec3(-4.3f, 0.5f, 2.0f));
		m_transComp->SetScale(Vec3(0.25f));
		//�^�O
		AddTag(L"Cheese");


	}

	void Cheese::OnUpdate()
	{
	}

	//Player�^�O�̎擾
	void Cheese::GetTag(shared_ptr<GameObject>& Player)
	{
		if (Player)
		{
			//Player��Cheese�̓�_�Ԃ̋����v�Z
			Vec3 playerPos = Player->GetComponent<Transform>()->GetPosition();
			Vec3 cheesePos = m_transComp->GetPosition();
			Vec3 distance = playerPos - cheesePos;

			if (distance.length() < 1.0f) {
				
				Vec3 distance = Vec3(playerPos - cheesePos).normalize();
				m_transComp->SetPosition(cheesePos + direction * 0.05f);
			}

		}

	}


}
//end basecross
