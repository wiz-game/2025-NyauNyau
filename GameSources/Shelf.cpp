
/*!
@file Ground.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Shelf::Shelf(const shared_ptr<Stage>& StagePtr,
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
	Shelf::~Shelf() {}

	void Shelf::OnCreate()
	{
		// �h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // �L���[�u�^�̃��b�V����ݒ肷��
		drawComp->SetOwnShadowActive(true); // �e���󂯓����
		drawComp->SetTextureResource(L"TEX_SHELF");

		// �g�����X�t�H�[���R���|�[�l���g�̎擾�Ɛݒ�
		//auto transComp = GetComponent<Transform>();
		//transComp->SetScale(10, 1, 10); // XZ�����Ɋg�傷��
		//transComp->SetPosition(0, -1.0f, 0);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

	}

	void Shelf::OnUpdate()
	{
	}

}
//end basecross
