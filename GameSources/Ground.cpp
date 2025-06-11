
/*!
@file Ground.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Ground::Ground(const shared_ptr<Stage>& StagePtr,
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
	Ground::~Ground() {}

	void Ground::OnCreate()
	{
		// �h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // �L���[�u�^�̃��b�V����ݒ肷��
		//drawComp->SetOwnShadowActive(true); // �e���󂯓����
		drawComp->SetTextureResource(L"TEX_YUKA");


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

	void Ground::OnUpdate()
	{
	}

	void Ground::OnCollisionEnter(shared_ptr<GameObject>& otherObject)
	{
		if (otherObject->FindTag(L"Player_0")) // "Player" �^�O�����I�u�W�F�N�g�ƏՓ�
		{
			auto scene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");

			//��莞�Ԍ�ɃX�v���C�g���폜����i�^�C�g����ʂ���Q�[���X�e�[�W�Ɉڂ�^�C�~���O�j
			PostEvent(5.0f, GetThis<ObjectInterface>(), scene, L"RemoveSprite");

		}
	}


}
//end basecross
