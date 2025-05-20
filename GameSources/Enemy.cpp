/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// �\�z�Ɣj��
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position), 
		isGameOver(false),
		EnemySpeed(5.58f)
	{
	}

	Enemy::~Enemy() {}


	void Enemy::OnCreate()
	{
		// �h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // �L���[�u�^�̃��b�V����ݒ肷��
		drawComp->SetTextureResource(L"TEX_ENEMY");
		SetAlphaActive(true);

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//�R���W����
		auto ptrColl = AddComponent<CollisionObb>();

		AddTag(L"Enemy");

	}


	void Enemy::OnUpdate()
	{
		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();

		// �V�[�����擾����
		auto scene = app->GetScene<Scene>();

		// �f�o�b�O���O���擾����
		wstring log = scene->GetDebugString();
		wstringstream wss(log);
		wss << L"\n\n\n\nGameOver:" << isGameOver;

		scene->SetDebugString(wss.str());

		auto ptrGra = AddComponent<Gravity>();

		// Transform �R���|�[�l���g���擾
		auto ptrTransform = GetComponent<Transform>();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		// ���݂̈ʒu���擾
		Vec3 currentPosition = ptrTransform->GetPosition();

		// �E������ `EnemySpeed` �����ړ�
		currentPosition.z += EnemySpeed * elapsedTime;

		// �X�V�����ʒu���Z�b�g
		ptrTransform->SetPosition(currentPosition);


	}


	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& otherObject)
	{
		if (otherObject->FindTag(L"Player_0")) // "Player" �^�O�����I�u�W�F�N�g�ƏՓ�
		{
			isGameOver = true; // �Q�[���I�[�o�[�t���O��ݒ�

			//auto scene = App::GetApp()->GetScene<Scene>();
			//PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");

			////��莞�Ԍ�ɃX�v���C�g���폜����i�^�C�g����ʂ���Q�[���X�e�[�W�Ɉڂ�^�C�~���O�j
			//PostEvent(5.0f, GetThis<ObjectInterface>(), scene, L"RemoveSprite");

		}

	}
}
//end basecross
