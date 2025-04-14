#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//�\�z�Ɣj��
	Player::Player(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_Speed(5.0f)
	{}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		return ret;
	}

	Vec3 Player::GetMoveVector() const
	{
		Vec3 angle(0, 0, 0);
		//���͂̎擾
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;	//���������̃X�s�[�h
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//�i�s�����̌������v�Z
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//�i�s������������̊p�x���Z�o
			float frontAngle = atan2(front.z, front.x);
			//�R���g���[���̌����v�Z
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//�R���g���[���̌�������p�x���v�Z
			float cntlAngle = atan2(-moveX, moveZ);
			//�g�[�^���̊p�x���Z�o
			float totalAngle = frontAngle + cntlAngle;
			//�p�x����x�N�g�����쐬
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//���K������
			angle.normalize();
			//�ړ��T�C�Y��ݒ�B
			angle *= moveSize;
			//X���͕ω������Ȃ�
			angle.x = 0;
		}
		return angle;
	}


	void Player::MovePlayer()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f) {
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
		}
		//��]�̌v�Z
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}
	}


	void Player::OnCreate()
	{
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(0.0f, 0.25f, 0.25f);	//���a25�Z���`�̋���
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(Vec3(-4.75f, 0.125f, 0));

		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionSphere>();

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();


		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetFogEnabled(true);


	}

	//void Player::MoveToWallPosition(const shared_ptr<GameObject>& Wall)
	//{
	//	// Wall��Transform�R���|�[�l���g����ʒu���擾
	//	auto wallTransform = Wall->GetComponent<Transform>();
	//	if (wallTransform)
	//	{
	//		auto wallPosition = wallTransform->GetPosition();

	//		// player��Transform�R���|�[�l���g���擾���Ĉʒu��ݒ�
	//		auto playerTransform = GetComponent<Transform>();
	//		if (playerTransform)
	//		{
	//			playerTransform->SetPosition(wallPosition);
	//		}
	//	}
	//}

	void Player::OnUpdate()
	{
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();

		// wall�I�u�W�F�N�g���擾�i��Ƃ��Ė��O�Ŏ擾����ꍇ�j
		/*auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall");
		if (wall)
		{
			MoveToWallPosition(wall);
		}*/

	}

	//A�{�^��
	void Player::OnPushA()
	{
		auto grav = GetComponent<Gravity>();
		grav->StartJump(Vec3(0, 4.0f, 0));
	}

}