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
		m_gravity(-2.0),
		m_Radius(0.0f),
		m_Center(0.0f,0.0f)




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

		m_Center = m_Position + Vec3(m_Scale.x / 2, m_Scale.y / 2, 0.0f);
		Vec3 position = Vec3(m_Center.x, m_Center.y, 0.0f);
		m_Radius = 10.0f;

		//�e�p�t�H�[�}���X�𓾂�
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);

		float texW = 50.0f / 512.0f; // ������1��50�s�N�Z���ɂ��Ă�
		float texH = 90.0f / 128.0f;
		float left = texW * m_number;
		float right = left + texW;
		float top = 100.0f;
		float bottom = top + texH; // �����̍��� / �e�N�X�`���̍���



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
		auto G = GetStage()->GetThis<GameStage>()->GetGameObjectVec();
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();
		//DrawStrings();
		MoveY();
		MoveXZ();

		auto& app = App::GetApp();
		//auto ptrTransform = GetComponent<Transform>(); // OnCreate�ŃL���b�V������m_Transform���g���Ă�OK
		//Vec2 currentPlayerPosition = ptrTransform->GetPosition();
		float elapsed = app->GetElapsedTime();
		float gravity = 0.0f;
		Vec2 acceleration = Vec2(0.0f, -gravity) * elapsed;
		static Vec2 velocity = Vec2();
		velocity += acceleration * elapsed;

		Vec2 position2D = GetCenter() + velocity * elapsed;
		SetCenter(position2D);

		auto scene = app->GetScene<Scene>();

		wstring log = scene->GetDebugString();
		wstringstream wss;
		wss << log;


		//auto ptrTransform = GetComponent<Transform>();
		Vec3 currentPosition = ptrTransform->GetPosition();
		m_Center.x = currentPosition.x+m_Scale.x/2;
		m_Center.y = currentPosition.y-m_Scale.y/2;
		m_Center.z = 0.0f;


		if (m_OtherPolygon)
		{
			// �e�̒��_�����[���h���W�ɕϊ�
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

			// �Փ˔�������s
			Vec3 mtv;
			if (ComputeMTV(worldVertices, mtv))
			{
				currentPosition += mtv*1.01; // �߂荞�񂾕��������߂�

				// ���x��␳����
				Vec3 collisionNormal = mtv;
				collisionNormal.normalize();

				// �����A������̔����i�n�ʂ���̔����j���󂯂���
				if (collisionNormal.y > 0.7f)
				{
					m_velocity.y = 0;
					m_isAir = false; // ���n�ʂɂ���̂�false
				}
				else
				{
					// �n�ʂ��痣�ꂽ�u��
					m_isAir = true; // �n�ʂɂ��Ȃ��̂�true
				}

				// === ���ׂĂ̌v�Z���I������ŏI�I�Ȉʒu��Transform�ɐݒ� ===
				ptrTransform->SetPosition(currentPosition);

			}

		}



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

		auto gameObjectVec = GetStage()->GetGameObjectVec();
		for (auto obj : gameObjectVec)
		{

			if (pos.y > -4.99f)
			{
				// �d�͂̓K�p
				float elapsedTime = App::GetApp()->GetElapsedTime();
				m_velocity.y += m_gravity * elapsedTime;
				//pos.y += m_velocity.y * elapsedTime;
				auto ptrGra = AddComponent<Gravity>();
				m_isAir = true;


			// �n�ʂƂ̏Փˎ��̏���
			//if (pos.y <= -4.99f)
			//{
			//	m_velocity.y = 0.0f; // ���x�����Z�b�g
			//	m_isAir = true; // �󒆏�Ԃ����Z�b�g
			//}



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
				m_velocity.y = 15.0f;
				m_isAir = true;
			}
				

			//if (m_isAir = false)
			//{
			//	m_velocity.y = 8.0f;
			//	m_isAir = true;
			//}


	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other)
	{
	if (dynamic_pointer_cast<Ground>(Other)) // �ՓˑΏۂ��n�ʂ��m�F
		{
			m_velocity.y = 0.0f; // ���x�����Z�b�g
			m_isAir = false; // �󒆏�Ԃ����Z�b�g

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
		//bool Player::ComputeMTV(const shared_ptr<ShadowObject>& polygon, const Vec3& sphereWorldCenter, float sphereRadius, Vec3& mtv)// �ύX��
	{
		// === �ϐ��̏����� ===
		//vector<Vec3> polygonVertices = polygonVertices->GetVertices();
		if (polygonVertices.empty()) {
			return false; // �|���S���ɒ��_���Ȃ���Δ���s�\
		}

		float minOverlap = FLT_MAX; // C++��float�̍ő�l (cfloat�w�b�_)
		Vec3 smallestAxis;          // �ŏ��̏d�Ȃ�𐶂񂾎���ۑ�����ϐ�

		std::vector<Vec3> axes;     // �e�X�g���ׂ��������ׂē���郊�X�g


		// === �������̌������ׂďW�߂� ===

		// 2a. �|���S���́u�ӂ̖@���v�����ׂă��X�g(axes)�ɒǉ�
		for (size_t i = 0; i < polygonVertices.size(); ++i) {
			Vec3 p1 = polygonVertices[i];
			Vec3 p2 = polygonVertices[(i + 1) % polygonVertices.size()];
			Vec3 normal = GetNormal(p1, p2); // ���O�ɏC������2D�@���֐���z��
			if (normal.length() > 1e-6f) { // �[���x�N�g���łȂ���Βǉ�
				axes.push_back(normal);
			}
		}

		// 2b. �~�̒��S�Ɂu�ł��߂����_�ւ̃x�N�g���v�����X�g(axes)�ɒǉ�
		Vec3 closestVertex;
		float minDistanceSq = FLT_MAX;
		for (const auto& vertex : polygonVertices) {
			// �����́u2��v�Ŕ�r���� (����)
			Vec3 diff = vertex - m_Center;
			float distSq = diff.dot(diff);
			if (distSq < minDistanceSq) {
				minDistanceSq = distSq;
				closestVertex = vertex;
			}
		}
		Vec3 axisToClosestVertex = closestVertex - m_Center;
		if (axisToClosestVertex.dot(axisToClosestVertex) > 1e-6f) {
			axisToClosestVertex.normalize();
			axes.push_back(axisToClosestVertex);
		}


		// ===  �W�߂����ŁA���������s�� ===
		for (const auto& axis : axes) {
			float minPoly, maxPoly, minCircle, maxCircle;
			ProjectOntoAxis(polygonVertices, axis, minPoly, maxPoly);
			ProjectCircleOntoAxis(m_Center, m_Radius, axis, minCircle, maxCircle);

			float overlap = min(maxPoly, maxCircle) - max(minPoly, minCircle);

			if (overlap <= 0.0f) {
				// �����������������I �����Ɂu�Փ˂��Ă��Ȃ��v�Ɣ��f���ďI��
				mtv = Vec3(0.0f, 0.0f, 0.0f);
				return false;
			}

			// �ŏ��̏d�Ȃ�L�^���X�V����
			if (overlap < minOverlap) {
				minOverlap = overlap;
				smallestAxis = axis;
			}
		}

		// === �ŏI�I�ȉ����o���x�N�g��(MTV)���v�Z ===
		// ���̎��_�ł��ׂĂ̎��ŏd�Ȃ肪�������̂ŁA�Փ˂��m�肵�Ă���

		// �����o���x�N�g�����v�Z
		mtv = smallestAxis * minOverlap;

		// MTV�̕����𐳂�������
		// �~�̒��S����|���S���̒��S�ւ̃x�N�g�����v�Z
		Vec3 polyCenter(0.0f, 0.0f, 0.0f);
		for (const auto& v : polygonVertices) polyCenter += v;
		polyCenter /= static_cast<float>(polygonVertices.size());

		// �~����|���S���֌����������ƁA���݂�mtv�̕������t�Ȃ�Amtv�𔽓]������
		Vec3 direction = polyCenter - m_Center;
		Vec3 potential_mtv = smallestAxis * minOverlap;
		for (const auto& v : polygonVertices) polyCenter += v;
		polyCenter /= static_cast<float>(polygonVertices.size());
		Vec3 centerToCenter = polyCenter - m_Center;

		if (centerToCenter.dot(potential_mtv) < 0.0f) {
			mtv = potential_mtv;
		}
		else {
			mtv = -potential_mtv;
		}


		return true; // �Փ˂������Ƃ�`����

	//	// �ŏ������o���x�N�g���̐��K��
	//	if (minAxis.length() > 1e-6f) {
	//		minAxis.normalize();
	//		mtv = minAxis * minOverlap;
	//		mtv *= -0.8f;
	//	}
	//	return true;

		//return true;
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();


	//	wstring log = scene->GetDebugString();
	//	wstringstream wss;
	//	wss << log;

		wss << polygonVertices.size();
	}
}
