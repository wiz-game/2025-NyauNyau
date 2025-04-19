#include "stdafx.h"
#include "Project.h"


namespace basecross
{
	//構築と破棄
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
		m_Player1()
	{}

	Vec2 Player::GetInputState() const {
		Vec2 ret;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;

		// 左スティックの状態を判定
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		return ret;
	}

	Vec3 Player::GetMoveVector() const
	{
		Vec3 angle(0, 0, 0);
		//入力の取得
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;
		if (moveX != 0 || moveZ != 0) {
			float moveLength = 0;	//動いた時のスピード
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//進行方向の向きを計算
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			//進行方向向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			//コントローラの向き計算
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(-moveX, moveZ);
			//トータルの角度を算出
			// float totalAngle = frontAngle + cntlAngle;
			float playerRotationY = XMConvertToRadians(m_Rotation.y + 90.0f); // プレイヤーのY軸回転を取得
			float totalAngle = frontAngle + cntlAngle + playerRotationY; // プレイヤー回転を考慮
			//角度からベクトルを作成
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//正規化する
			angle.normalize();
			//移動サイズを設定
			angle *= moveSize;
			//x軸を固定
			angle.x = 0;

			if (m_Player1)
			{
				moveX = inPut.y;
				moveZ = inPut.x;

				angle.z = 0;
				angle.x = 1;
			}


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
		//回転の計算
		if (angle.length() > 0.0f) {
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(angle, 1.0f);
		}

		
	}


	void Player::OnCreate()
	{
		//初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(m_Scale);	//直径25センチの球体
		ptr->SetRotation(m_Rotation);
		ptr->SetPosition(m_Position);
		//ptr->SetScale(0.0f, 0.25f, 0.25f);	//直径25センチの球体
		//ptr->SetRotation(0.0f, 0.0f, 0.0f);
		//ptr->SetPosition(Vec3(-4.75f, 0.125f, -5.0f));

		//CollisionSphere衝突判定を付ける
		auto ptrColl = AddComponent<CollisionSphere>();


		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


		//重力をつける
		auto ptrGra = AddComponent<Gravity>();


		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");
		ptrDraw->SetFogEnabled(true);



	}



	void Player::MoveToWallPosition(const shared_ptr<GameObject>& wall)
	{

		/*if (GetThis<GameObject>()->FindTag(L"Wall_0"))
		{
			auto playerTransform = GetComponent<Transform>();
			playerTransform->SetRotation(0, XMConvertToRadians(90), 0);
		}*/

		//// WallのTransformコンポーネントから位置を取得
		//auto wallTransform = Wall->GetComponent<Transform>();
		//if (wallTransform)
		//{
		//	auto wallPosition = wallTransform->GetPosition();

		//	// playerのTransformコンポーネントを取得して位置を設定
		//	auto playerTransform = GetComponent<Transform>();
		//	if (playerTransform)
		//	{
		//		playerTransform->SetPosition(wallPosition);
		//	}
		//}
	}

	void Player::OnUpdate()
	{
		auto G = GetStage()->GetThis<GameStage>()->GetGameObjectVec();
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();
		SetPlayerMove(false);
		//MoveToWallPosition(GetThis<GameObject>());
		


	}

	//Aボタン
	void Player::OnPushA()
	{
			auto grav = GetComponent<Gravity>();
			auto pos = GetComponent<Transform>()->GetPosition();

			if (!m_isAir)
			{
				m_isAir = true;
				grav->StartJump(Vec3(0, 4.0f, 0));
			}
			else
			{

				if (pos.y < 0.125)
				{
					pos.y = 0.125f;
					m_isAir = false;
					grav->StartJump(Vec3(0, 0.0f, 0));

				}
			}


	}

	void Player:: SetPlayerMove(bool Player1)
	{
		m_Player1 = Player1;
	}




}
