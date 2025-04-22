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
		m_Player1(false),
		m_cameraAngleY(0.0f),
		m_forward(0.0f),
		m_velocityY(0.0f),
		m_velocity(0.0f),
		m_collisionFlag(false),
		m_gravity(-9.8)




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
			//float moveLength = 0;	//動いた時のスピード
			//auto ptrTransform = GetComponent<Transform>();
			//auto ptrCamera = OnGetDrawCamera();
			////進行方向の向きを計算
			//auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			//front.y = 0;
			//front.normalize();
			////進行方向向きからの角度を算出
			//float frontAngle = atan2(front.z, front.x);
			////コントローラの向き計算
			//Vec2 moveVec(moveX, moveZ);
			//float moveSize = moveVec.length();
			////コントローラの向きから角度を計算
			//float cntlAngle = atan2(-moveX, moveZ);
			////トータルの角度を算出
			//// float totalAngle = frontAngle + cntlAngle;
			//float playerRotationY = XMConvertToRadians(m_Rotation.y + 90.0f); // プレイヤーのY軸回転を取得
			//float totalAngle = frontAngle + cntlAngle + playerRotationY; // プレイヤー回転を考慮
			////角度からベクトルを作成
			//angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			////正規化する
			//angle.normalize();
			////移動サイズを設定
			//angle *= moveSize;

			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();

			// プレイヤーの回転角を考慮
			//float playerRotationY = XMConvertToRadians(m_Rotation.y);

			// カメラ方向からの角度
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			float frontAngle = -atan2(front.z, front.x);

			// スティック入力の角度
			Vec2 moveVec(moveX, moveZ);
			float cntlAngle = atan2(-moveX, moveZ);

			// 合計角度計算（カメラ + スティック + プレイヤー回転）
			float totalAngle = frontAngle + cntlAngle ;

			// 角度から移動ベクトルを作成
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			angle.normalize();

			// 移動サイズの適用
			angle *= moveVec.length();

			if (m_Player1)
			{
				//z軸を固定
				angle.z = 0;
			}
			else
			{
				//x軸を固定
				angle.x = 0;
			}


		}
		return angle;
	}


	void Player::MovePlayer()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * m_Speed;
			GetComponent<Transform>()->SetPosition(pos);
		}


		//auto transform = GetComponent<Transform>();
		//auto rotation = transform->GetRotation();
		//rotation.y = XMConvertToRadians(90);
		//transform->SetRotation(rotation);

		//回転の計算
		//if (angle.length() > 0.0f) {
		//	auto utilPtr = GetBehavior<UtilBehavior>();
		//	utilPtr->RotToHead(angle, 1.0f);
		//}

		
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

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

	}


	void Player::OnUpdate()
	{
		auto G = GetStage()->GetThis<GameStage>()->GetGameObjectVec();
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();
		DrawStrings();
		MoveY();
		MoveXZ();

		//// アプリケーションオブジェクトを取得する
		//auto& app = App::GetApp();
		//// シーンを取得する（ステージを管理するオブジェクト）
		//auto scene = app->GetScene<Scene>();
		//// インプットデバイスオブジェクトを取得する
		//auto& device = app->GetInputDevice();
		//// コントローラーオブジェクトを取得する
		//auto& pad = device.GetControlerVec()[0];

		//// 経過時間(Delta Time)を取得する
		//float delta = app->GetElapsedTime(); // 60FPS -> 1/60 -> 0.01666667f, 30FPS -> 1/30 -> 0.03333334f

		//// ステージを取得する
		//auto stage = dynamic_pointer_cast<GameStage>(GetStage());
		//Vec3 LStick(pad.fThumbLX, 0.0f, pad.fThumbLY);

		//float length = LStick.length();
		//if (length != 0.0f) // スティックが傾いているか
		//{
		//	// カメラの傾きに合わせて移動方向ベクトルを変更する
		//	float stickAngle = atan2f(LStick.z, LStick.x); // スティックのベクトルを角度(ラジアン)に変換する
		//	float forwardAngle = stickAngle + m_cameraAngleY + XM_PIDIV2; // スティックの傾きにカメラの回り込みを加算することで、カメラ基準の方向に変換する
		//	m_forward = Vec3(cosf(forwardAngle), 0.0f, sinf(forwardAngle));
		//}

		//auto grav = GetComponent<Gravity>();
		//auto pos = GetComponent<Transform>()->GetPosition();


		//if (pad.wPressedButtons & XINPUT_GAMEPAD_A)
		//{

		//	if (!m_isAir)
		//	{
		//		m_isAir = true;
		//		grav->StartJump(Vec3(0, 4.0f, 0));
		//	}
		//}

		//if(m_isAir)
		//{
		//	// ジャンプや落下の処理
		//	pos.y += m_velocityY; // 縦方向の移動
		//	m_velocityY += -0.98f * delta; // 速度を下げる処理

		//	if (pos.y < 0.125)
		//	{
		//		pos.y = 0.125f;
		//		m_isAir = false;
		//		grav->StartJump(Vec3(0.0f, 0.0f, 0.0f));

		//	}
		//}

		//GetComponent<Transform>()->SetPosition(pos); // 更新した座標を適用する


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
		//前回のターンからの時間
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_velocity.y += m_gravity * elapsedTime;
	}


	//Aボタン
	void Player::OnPushA()
	{ 

		m_velocity.y = 4.0f;

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


		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);

	}
}
