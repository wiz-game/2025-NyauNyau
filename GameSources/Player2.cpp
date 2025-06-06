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
		DrawStrings();
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


		if (m_OtherPolygon)
		{
			Vec2 mtv;
			//if (ComputeMTV(m_OtherPolygon, mtv))
			//{
			//	if (mtv.length() > 1e-6f)
			//	{
			//		Vec2 newCenter = m_Center + mtv;
			//		SetCenter(newCenter);
			//	}
			//}
		}

		Vec3 position = Vec3(m_Center.x, m_Center.y, 0.0f);
		//m_Transform->SetPosition(position);



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
		//auto pos = GetComponent<Transform>()->GetPosition();

	
			//if (pos.y == 0.502f || pos.y == 0.501f)
			//{
			//pos.y = 0.70f;
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
		if (dynamic_pointer_cast<Ground>(Other) || dynamic_pointer_cast<ShadowFloor>(Other)) // �ՓˑΏۂ��n�ʂ��m�F
		{
			m_velocity.y = 0.0f; // ���x�����Z�b�g
			m_isAir = false; // �󒆏�Ԃ����Z�b�g

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

	//bool Player::ComputeMTV(const shared_ptr<ShadowObject>& polygon, Vec2& mtv)
	////bool Player::ComputeMTV(const shared_ptr<ShadowObject>& polygon, const Vec3& sphereWorldCenter, float sphereRadius, Vec3& mtv)// �ύX��
	//{
	//	float minOverlap = 1000000.0f; // �����l���\���ɑ傫���ݒ�
	//	Vec3 minAxis = { 0.0f, 0.0f, 0.0f};

	//	vector<Vec3> polygonVertices = polygon->GetVertices();
	//	vector<Vec2> edges;

	//	//vector<Vec3> axes;	

	//	for (size_t i = 0; i < polygonVertices.size(); i++)
	//	{
	//		edges.push_back(GetNormal(polygonVertices[i], polygonVertices[(i + 1) % polygonVertices.size()]));
	//	}

	//	for (const auto& axis : edges)
	//	{
	//		float minPoly, maxPoly, minCircle, maxCircle;
	//		ProjectOntoAxis(polygonVertices, axis, minPoly, maxPoly);
	//		ProjectCircleOntoAxis(m_Center, m_Radius, axis, minCircle, maxCircle);
	//		//ProjectRectangleOntoAxis();

	//		float overlap = min(maxPoly, maxCircle) - max(minPoly, minCircle);

	//		if (overlap <= 0)
	//		{
	//			return false; // �d�Ȃ��Ă��Ȃ��ꍇ
	//		}

	//		if (overlap < minOverlap)
	//		{
	//			minOverlap = overlap;
	//			minAxis = axis;
	//		}
	//	}

	//	// �ŏ������o���x�N�g���̐��K��
	//	if (minAxis.length() > 1e-6f) {
	//		minAxis.normalize();
	//		mtv = minAxis * minOverlap;
	//		mtv *= -0.8f;
	//	}
	//	return true;

	//	auto& app = App::GetApp();
	//	auto scene = app->GetScene<Scene>();


	//	wstring log = scene->GetDebugString();
	//	wstringstream wss;
	//	wss << log;


	//}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& collision)
	{

	}
}
