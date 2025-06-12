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
		m_gravity(-4.0),
		m_Radius(0.0f),
		m_Center(0.0f,0.0f,0.0f)




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

			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();

			// �J������������̊p�x
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			float frontAngle = -atan2(front.z, front.x);

			// �X�e�B�b�N���͂̊p�x
			Vec2 moveVec(moveX, moveZ);
			float cntlAngle = atan2(-moveX, moveZ);

			// ���v�p�x�v�Z�i�J���� + �X�e�B�b�N + �v���C���[��]�j
			float totalAngle = frontAngle + cntlAngle;

			// �p�x����ړ��x�N�g�����쐬
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			angle.normalize();

			// �ړ��T�C�Y�̓K�p
			angle *= moveVec.length();

			//if (m_Player1)
			//{
				//z�����Œ�
				angle.z = 0;
			//}
			//else
			//{
			//	//x�����Œ�
			//	angle.x = 0;
			//}


		}
		return angle;
	}


	void Player::MovePlayer()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		auto pos = GetComponent<Transform>()->GetPosition();

		// x�����Ɏ����ړ�
		pos.x += elapsedTime * m_Speed;


		GetComponent<Transform>()->SetPosition(pos); // �X�V��


	}

	void Player::Jump(shared_ptr<GameObject>& jump)
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		auto pos = GetComponent<Transform>()->GetPosition();
		//�d�͂�����
		auto ptrGra = AddComponent<Gravity>();

		//auto gameObjectVec = GetGameObjectVec();
		//for (auto obj : gameObjectVec)
		//{
		//if (dynamic_pointer_cast<Box>())
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



		//Collision�Փ˔����t����
		auto ptrColl = AddComponent<CollisionObb>();

		//ptrColl->SetMakedSize(2.5f);

		m_Center = Vec3(1.2f, 0.6f, 0.3f);
		Vec3 position = Vec3(m_Center.x, m_Center.y, 0.0f);

		//�����蔻��̃T�C�Y
		m_Radius = m_Scale.y/2;

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		ptrDraw->SetTextureResource(L"TEX_NEZUMI2");
		//ptrDraw->SetTextureResource(L"TEX_NEZUMI");


		SetAlphaActive(true);


		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));


        auto objects = GetStage()->GetGameObjectVec();
		for (auto& obj : objects)
		{
			auto result = dynamic_pointer_cast<ShadowObject>(obj);
			if (result)
			{
				m_OtherPolygon = result;
				break;
			}
		}




		auto pos = GetComponent<Transform>()->GetPosition();
		auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
		Vec3 wallPoint = wall->GetWallPosition();

		pos.z = wallPoint.z;


	}


	void Player::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();

		//���͂Əd�͂Ɋ�Â��āA���̃t���[���̑��x(m_velocity)�����肷��
		m_InputHandler.PushHandle(GetThis<Player>()); // �W�����v����(OnPushA)�̎�t

		// X�����̈ړ����x�i�����ŉE�ɐi�ށj
		m_velocity.x = m_Speed;

		// Y�����̈ړ����x�i��ɏd�͂�K�p����j
		// �n�ʂɂ��邩�ǂ����́A���̌�̏Փ˔���Ŕ��f����
		m_velocity.y += m_gravity * elapsedTime;
		m_isAir = true; // ��{�I�ɋ󒆂ɂ���Ɖ��肵�A�n�ʂɂ�������false�ɂ���
		MoveY();

		//���x�Ɋ�Â��āA�v���C���[���u���Ɂv�ړ�������
		auto ptrTransform = GetComponent<Transform>();
		Vec3 currentPosition = ptrTransform->GetPosition();
		currentPosition += m_velocity * elapsedTime;


		//�Փ˔���Ɖ���

		// ����Ɏg���~�̒��S�́A�ړ���̃v���C���[�̈ʒu���̂���
		m_Center = currentPosition;
		// ���a�̓X�P�[���̔���
		m_Radius = m_Scale.x / 2.0f;


		if (m_OtherPolygon)
		{
			// 1. �e�̒��_�����[���h���W�ɕϊ�
			auto shadowTransform = m_OtherPolygon->GetComponent<Transform>();
			Mat4x4 shadowWorldMatrix = shadowTransform->GetWorldMatrix();
			std::vector<Vec3> localVertices = m_OtherPolygon->GetVertices();
			std::vector<Vec3> worldVertices;
			worldVertices.reserve(localVertices.size());
			for (const Vec3& localPos : localVertices)
			{
				Vec3 worldPos = localPos * shadowWorldMatrix;
				worldVertices.push_back(worldPos);
			}

			//�Փ˔�������s
			Vec3 mtv;
			if (ComputeMTV(worldVertices, mtv))
			{
				// --- �Փ˂����ꍇ�̕␳���� ---

				//�ʒu��␳����i1%���߂ɉ����o���j
				currentPosition += mtv * 1.01f;

				//���x��␳����
				Vec3 collisionNormal = mtv;
				collisionNormal.normalize();

				//������̔����i�n�ʁj���󂯂���
				if (collisionNormal.y > 0.7f)
				{
					m_velocity.y = 0; // Y���x�����Z�b�g
					m_isAir = false;  // �n��ɂ���
				}
				// �������̔����i�ǁj���󂯂���
				if (abs(collisionNormal.x) > 0.7f)
				{
					m_velocity.x = 0; // X���x�����Z�b�g
				}
			}
		}

		// ��΍��W�ł̒n�ʏ����i�ی��j
		if (currentPosition.y < -4.99f) {
			currentPosition.y = -4.99f;
			m_velocity.y = 0;
			m_isAir = false;
		}


		//�ŏI�I�Ȉʒu��Transform�ɐݒ� 
		ptrTransform->SetPosition(currentPosition);

		DrawStrings();
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


		if (pos.y > -4.99f)
		{
			// �d�͂̓K�p
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_velocity.y += m_gravity * elapsedTime;
			//pos.y += m_velocity.y * elapsedTime;
			auto ptrGra = AddComponent<Gravity>();
			m_isAir = false;


			// �n�ʂƂ̏Փˎ��̏���
			//if (pos.y <= -4.99f)
			//{
			//	m_velocity.y = 0.0f; // ���x�����Z�b�g
			//	m_isAir = true; // �󒆏�Ԃ����Z�b�g
			//}



			ptrTransform->SetPosition(pos);

		}
	}

	//A�{�^��
	void Player::OnPushA()
	{
		auto pos = GetComponent<Transform>()->GetPosition();

		//if (pos.y == 0.502f || pos.y == 0.501f)
		//{
		//}


		if (m_isAir == false)
		{
			m_velocity.y = 8.0f; // �W�����v�̏�����^����
			m_isAir = true; // �W�����v�����̂ŋ󒆏�Ԃɂ���
		}

	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other)
	{
	if (dynamic_pointer_cast<Ground>(Other)) // �ՓˑΏۂ��n�ʂ��m�F
		{

			m_velocity.y = 0;
			m_isAir = false;
			//m_collisionFlag = true;
		}
	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		m_collisionFlag = false;
	}


	void Player::SetPlayerMove(bool Player1)
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

	bool Player::ComputeMTV(const std::vector<Vec3>& polygonVertices, Vec3& mtv)
	{
		// �|���S���ɕӂ��Ȃ���΁i���_��2�����Ȃ�j����s�\
		if (polygonVertices.size() < 2) {
			return false;
		}

		// === �X�e�b�v1: �|���S���̊O����ŁA�~�̒��S�ɍł��߂��_(closestPointOnPolygon)��T�� ===
		Vec3 closestPointOnPolygon;
		float minDistanceSq = FLT_MAX; // �ŏ������́u2��v���L�^����ϐ�

		for (size_t i = 0; i < polygonVertices.size(); ++i)
		{
			Vec3 p1 = polygonVertices[i];
			Vec3 p2 = polygonVertices[(i + 1) % polygonVertices.size()]; // ���̒��_�i���X�g�̍Ō�͍ŏ��ɖ߂�j

			// ���ݒ��ׂĂ���ӂ̃x�N�g��
			Vec3 edge = p2 - p1;

			// �ӂ̎n�_p1����~�̒��Sm_Center�ւ̃x�N�g��
			Vec3 vecToCenter = m_Center - p1;

			// �Ӄx�N�g�����[���x�N�g���łȂ����Ƃ��m�F
			float edgeLengthSq = edge.dot(edge);
			if (edgeLengthSq < 1e-9f) {
				continue; // ���̕ӂ͒������Ȃ��̂ŃX�L�b�v
			}

			// �~�̒��S���A��p1-p2�̂ǂ̈ʒu�Ɏˉe����邩���v�Z (0.0�`1.0�̔䗦t)
			float t = vecToCenter.dot(edge) / edgeLengthSq;

			// t��0.0����1.0�͈̔͂ɃN�����v�i�����j����
			// ����ɂ��A�ŋߖT�_���K���ӂ̏�i���[�̒��_���܂ށj�Ɍ��肳���
			if (t > 1.0f) {
				t = 1.0f;
			}
			if (t < 0.0f) {
				t = 0.0f;
			};

			// �ӏ�ł̍ł��߂��_���v�Z
			Vec3 closestPointOnEdge = p1 + edge * t;

			// ���̓_�Ɖ~�̒��S�Ƃ̋����i��2��j���v�Z
			float distSq = (m_Center - closestPointOnEdge).dot(m_Center - closestPointOnEdge);

			// ���܂ł̍ŒZ�L�^�����߂���΁A�L�^���X�V
			if (distSq < minDistanceSq)
			{
				minDistanceSq = distSq;
				closestPointOnPolygon = closestPointOnEdge;
			}
		}

		// === �X�e�b�v2: �Փ˂��Ă��邩���� ===
		// �~�̒��S�ƃ|���S����̍ŋߖT�_�Ƃ̋������A�~�̔��a���傫�����H
		if (minDistanceSq >= m_Radius * m_Radius)
		{
			// ����Ă���A�܂��͂��傤�ǐڂ��Ă��� -> �Փ˂��Ă��Ȃ�
			mtv = Vec3(0.0f, 0.0f, 0.0f);
			return false;
		}

		// --- ��������͏Փ˂��Ă��邱�Ƃ��m�� ---

		// === �X�e�b�v3: �����o���x�N�g��(MTV)���v�Z ===

		// �����o�������́A�|���S����̍ŋߖT�_����~�̒��S�֌���������
		Vec3 pushDirection = m_Center - closestPointOnPolygon;

		// �������S�_�����S�ɏd�Ȃ��Ă���ȂǁA�[���x�N�g���ɂȂ�����A���̉����o�������i������Ȃǁj���g��
		if (pushDirection.dot(pushDirection) < 1e-9f) {
			pushDirection = Vec3(0.0f, 1.0f, 0.0f);
		}
		else {
			pushDirection.normalize();
		}

		// �����o���ʂ́A���a�Ǝ��ۂ̋����̍�
		float overlap = m_Radius - sqrt(minDistanceSq);

		// �ŏI�I��MTV���v�Z
		mtv = pushDirection * overlap;

		return true; // �Փ˂������Ƃ�`����
	}
}
