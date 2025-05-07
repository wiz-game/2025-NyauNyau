#include "stdafx.h"
#include "Project.h"


namespace basecross
{
	//�\�z�Ɣj��
	Player::Player(const shared_ptr<Stage>& StagePtr,
		Vec3& Scale,
		Vec3& Rotation,
		Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_Speed(5.0f),
		m_isAir(false),
		m_Player1(false),
		m_cameraAngleY(0.0f),
		m_forward(0.0f),
		m_velocityY(0.0f),
		m_velocity(0.0f),
		m_collisionFlag(false),
		m_gravity(-9.0)



	{}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;

		// ���X�e�B�b�N�̏�Ԃ𔻒�
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
			//float moveLength = 0;	//���������̃X�s�[�h
			//auto ptrTransform = GetComponent<Transform>();
			//auto ptrCamera = OnGetDrawCamera();
			////�i�s�����̌������v�Z
			//auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			//front.y = 0;
			//front.normalize();
			////�i�s������������̊p�x���Z�o
			//float frontAngle = atan2(front.z, front.x);
			////�R���g���[���̌����v�Z
			//Vec2 moveVec(moveX, moveZ);
			//float moveSize = moveVec.length();
			////�R���g���[���̌�������p�x���v�Z
			//float cntlAngle = atan2(-moveX, moveZ);
			////�g�[�^���̊p�x���Z�o
			//// float totalAngle = frontAngle + cntlAngle;
			//float playerRotationY = XMConvertToRadians(m_Rotation.y + 90.0f); // �v���C���[��Y����]���擾
			//float totalAngle = frontAngle + cntlAngle + playerRotationY; // �v���C���[��]���l��
			////�p�x����x�N�g�����쐬
			//angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			////���K������
			//angle.normalize();
			////�ړ��T�C�Y��ݒ�
			//angle *= moveSize;

			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();

			// �v���C���[�̉�]�p���l��
			//float playerRotationY = XMConvertToRadians(m_Rotation.y);

			// �J������������̊p�x
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			float frontAngle = -atan2(front.z, front.x);

			// �X�e�B�b�N���͂̊p�x
			Vec2 moveVec(moveX, moveZ);
			float cntlAngle = atan2(-moveX, moveZ);

			// ���v�p�x�v�Z�i�J���� + �X�e�B�b�N + �v���C���[��]�j
			float totalAngle = frontAngle + cntlAngle ;

			// �p�x����ړ��x�N�g�����쐬
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			angle.normalize();

			// �ړ��T�C�Y�̓K�p
			angle *= moveVec.length();

			if (m_Player1)
			{
				//z�����Œ�
				angle.z = 0;
			}
			else
			{
				//x�����Œ�
				angle.x = 0;
			}


		}
		return angle;
	}


	void Player::MovePlayer()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		auto pos = GetComponent<Transform>()->GetPosition();

		// z�����Ɏ����ړ�
		pos.z += elapsedTime * m_Speed;


		GetComponent<Transform>()->SetPosition(pos); // �X�V��




		/*if (angle.length() > 0.0f)
		{
			GetComponent<Transform>()->SetPosition(pos);
		}*/

		//��]�̌v�Z
		//if (angle.length() > 0.0f) {
		//	auto utilPtr = GetBehavior<UtilBehavior>();
		//	utilPtr->RotToHead(angle, 1.0f);
		//}

		
	}

	void Player::Jump(shared_ptr<GameObject>& jump)
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		auto pos = GetComponent<Transform>()->GetPosition();
		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();

		//if (jump->FindTag(L"BOX"))
		//{
		//	if (pos.y == 0.502f || pos.y == 0.501f)
		//	{
		//		pos.y = 0.50f; 
		//	}


		//	if (pos.y == 0.50f)
		//	{
		//		m_velocity.y = 8.0f;
		//		//m_isAir = true;
		//	}

		//}
	}


	void Player::OnCreate()
	{
		//�����ʒu�Ȃǂ̐ݒ�
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(m_Scale);	//���a25�Z���`�̋���
		ptr->SetRotation(m_Rotation);
		ptr->SetPosition(m_Position);
		//ptr->SetScale(0.0f, 0.25f, 0.25f);	//���a25�Z���`�̋���
		//ptr->SetRotation(0.0f, 0.0f, 0.0f);
		//ptr->SetPosition(Vec3(-4.75f, 0.125f, -5.0f));

		//CollisionSphere�Փ˔����t����
		auto ptrColl = AddComponent<CollisionSphere>();


		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetTextureResource(L"TEX_NEZUMI2");
		//ptrDraw->SetTextureResource(L"TEX_NEZUMI");


		
		SetAlphaActive(true);



		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));



	}


	void Player::OnUpdate()
	{
		auto G = GetStage()->GetThis<GameStage>()->GetGameObjectVec();
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();
		DrawStrings();
		MoveY();
		MoveXZ();
		

		auto ptrDraw = AddComponent<BcPNTStaticDraw>();


		//auto moveVector = GetMoveVector(); // �v���C���[�̈ړ��x�N�g�����擾

		//if (moveVector.z > 0.0f)
		//{
		//	ptrDraw->SetTextureResource(L"TEX_NEZUMI2");
		//}

		//if (moveVector.z < 0.0f)
		//{
		//	ptrDraw->SetTextureResource(L"TEX_NEZUMI");

		//}


	}
	

	void Player::MoveXZ() {
		auto angle = GetInputState();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = GetComponent<Transform>()->GetPosition();
		pos += elapsedTime * m_velocity;
		GetComponent<Transform>()->SetPosition(pos);
	}


	void Player::MoveY() {
		auto ptrTransform = GetComponent<Transform>();
		auto pos = GetComponent<Transform>()->GetPosition();


		if (pos.y > 0.50f)
		{
			// �d�͂̓K�p
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_velocity.y += m_gravity * elapsedTime;
			//pos.y += m_velocity.y * elapsedTime;
			auto ptrGra = AddComponent<Gravity>();



			// �n�ʂƂ̏Փˎ��̏���
			if (pos.y <= 0.50f)
			{
				m_velocity.y = 0.0f; // ���x�����Z�b�g
				m_isAir = false; // �󒆏�Ԃ����Z�b�g
			}

			ptrTransform->SetPosition(pos);



			////�d�͂�����
			//auto ptrGra = AddComponent<Gravity>();

			////�O��̃^�[������̎��� 
			//float elapsedTime = App::GetApp()->GetElapsedTime();
			//m_velocity.y += m_gravity * elapsedTime;

			//if (pos.y <= 0.0f) // �v���C���[�����n�����ꍇ
			//{
			//	pos.y = 0.0f;  // �n�ʂɃ��Z�b�g
			//	m_velocity.y = 0.0f; // �������̑��x���~
			//  m_isAir = false; // �󒆏�Ԃ����Z�b�g
			//}

		}
	}

	//A�{�^��
	void Player::OnPushA()
	{ 
		auto pos = GetComponent<Transform>()->GetPosition();

		if (pos.y == 0.502f || pos.y == 0.501f)
		{
			pos.y = 0.50f; 
		}


		if (pos.y == 0.50f)
		{
			m_velocity.y = 8.0f;
			//m_isAir = true;
		}

	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other) 
	{
		if (Other->FindTag(L"Ground")) // �ՓˑΏۂ��n�ʂ��m�F
		{

			m_velocity.y = 0;
			//m_collisionFlag = true;
		}
	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& Other) 
	{
		m_collisionFlag = false;
	}


	void Player:: SetPlayerMove(bool Player1)
	{
		m_Player1 = Player1;
	}

	void Player::DrawStrings()
	{
		auto pos = GetComponent<Transform>()->GetPosition();
		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring str = positionStr;


		//������R���|�[�l���g�̎擾
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);

	}
}
