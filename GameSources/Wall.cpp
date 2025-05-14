/*!
@file Wall.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Wall::Wall(const shared_ptr<Stage>& StagePtr,
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
	Wall::~Wall() {}

	//������
	void Wall::OnCreate() {
		// �h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SQUARE"); // �L���[�u�^�̃��b�V����ݒ肷��
		//drawComp->SetTextureResource(L"TEX_KABE");
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//�R���W��������
		/*auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);*/
		drawComp->SetRasterizerState(RasterizerState::Wireframe);
	}

	void Wall::OnUpdate()
	{
	}

	//�ǂ̖@�����擾
	Vec3 Wall::GetWallNormal() const
	{
		return GetComponent<Transform>()->GetForward();
	}

	//�ǂ̈ʒu���擾
	Vec3 Wall::GetWallPosition() const
	{
		return GetComponent<Transform>()->GetPosition();

	}
}
//end basecross
