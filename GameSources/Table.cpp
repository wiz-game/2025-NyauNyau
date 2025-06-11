
/*!
@file Ground.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Table::Table(const shared_ptr<Stage>& StagePtr,
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
	Table::~Table() {}

	void Table::OnCreate()
	{
		// �h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		//drawComp->SetMeshResource(L"DEFAULT_CUBE"); // �L���[�u�^�̃��b�V����ݒ肷��
		//drawComp->SetOwnShadowActive(true); // �e���󂯓����
		//auto drawComp = AddComponent<PNTStaticDraw>();

		InitDrawComp();

		// �g�����X�t�H�[���R���|�[�l���g�̎擾�Ɛݒ�
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

	}

	void Table::OnUpdate()
	{
	}

	void Table::InitDrawComp()
	{
		//Mat4x4 span;
		//span.affineTransformation(Vec3(1.0f), Vec3(), Vec3(), Vec3(0.0f, 0.0f, 0.0f));


		m_drawComp = AddComponent<PNTStaticModelDraw>();
		m_drawComp->SetMultiMeshResource(L"MODEL_TABLE");

		//m_drawComp->SetMeshToTransformMatrix(span);
	}


}
//end basecross
