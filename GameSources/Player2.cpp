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
		m_gravity(-9.0),
		m_Radius(0.0f),
		m_Center(0.0f,0.0f,0.0f)




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
			float totalAngle = frontAngle + cntlAngle;

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
		auto pos = GetComponent<Transform>()->GetPosition();

		// z方向に自動移動
		pos.x += elapsedTime * m_Speed;


		GetComponent<Transform>()->SetPosition(pos); // 更新後




		/*if (angle.length() > 0.0f)
		{
			GetComponent<Transform>()->SetPosition(pos);
		}*/

		//回転の計算
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
		//重力をつける
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
		//初期位置などの設定
		auto ptr = AddComponent<Transform>();
		ptr->SetScale(m_Scale);	//直径25センチの球体
		ptr->SetRotation(m_Rotation);
		ptr->SetPosition(m_Position);
		//ptr->SetScale(0.0f, 0.25f, 0.25f);	//直径25センチの球体
		//ptr->SetRotation(0.0f, 0.0f, 0.0f);
		//ptr->SetPosition(Vec3(-4.75f, 0.125f, -5.0f));

		//Collision衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();

		m_Center = Vec3(1.2f, 0.6f, 0.3f);
		m_Radius = 0.1f;

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetTextureResource(L"TEX_NEZUMI2");
		//ptrDraw->SetTextureResource(L"TEX_NEZUMI");


		SetAlphaActive(true);


		//文字列をつける
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

		

		{
			Vec3 mtv;
			if (ComputeMTV(m_OtherPolygon, mtv))
			{
				if (mtv.length() > 1e-6f)
				{
					Vec3 newCenter = m_Center + mtv;
				}
			}
		}
	
		


		//auto moveVector = GetMoveVector(); // プレイヤーの移動ベクトルを取得

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


		if (pos.y > -4.00f)
		{
			// 重力の適用
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_velocity.y += m_gravity * elapsedTime;
			//pos.y += m_velocity.y * elapsedTime;
			auto ptrGra = AddComponent<Gravity>();



			// 地面との衝突時の処理
			if (pos.y <= -4.0f)
			{
				m_velocity.y = 0.0f; // 速度をリセット
				m_isAir = false; // 空中状態をリセット
			}

			ptrTransform->SetPosition(pos);



			////重力をつける
			//auto ptrGra = AddComponent<Gravity>();

			////前回のターンからの時間 
			//float elapsedTime = App::GetApp()->GetElapsedTime();
			//m_velocity.y += m_gravity * elapsedTime;

			//if (pos.y <= 0.0f) // プレイヤーが着地した場合
			//{
			//	pos.y = 0.0f;  // 地面にリセット
			//	m_velocity.y = 0.0f; // 下方向の速度を停止
			//  m_isAir = false; // 空中状態をリセット
			//}

		}
	}

	//Aボタン
	void Player::OnPushA()
	{
		auto pos = GetComponent<Transform>()->GetPosition();

		//if (pos.y == 0.502f || pos.y == 0.501f)
		//{
		pos.y = 0.50f;
		//}


		if (pos.y == 0.50f)
		{
			m_velocity.y = 8.0f;
			//m_isAir = true;
		}

	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other)
	{
		if (Other->FindTag(L"Ground")) // 衝突対象が地面か確認
		{

			m_velocity.y = 0;
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
		


		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);

	}

	bool Player::ComputeMTV(const shared_ptr<ShadowObject>& polygon, Vec3& mtv)
	{
		float minOverlap = 1000000.0f; // 初期値を十分に大きく設定
		Vec2 minAxis = { 0.0f, 0.0f };

		vector<Vec3> polygonVertices = polygon->GetVertices();
		vector<Vec3> edges;
		for (size_t i = 0; i < polygonVertices.size(); i++)
		{
			edges.push_back(GetNormal(polygonVertices[i], polygonVertices[(i + 1) % polygonVertices.size()], polygonVertices[(i + 2) % polygonVertices.size()]));
		}

		for (const auto& axis : edges)
		{
			float minPoly, maxPoly, minCircle, maxCircle;
			ProjectOntoAxis(polygonVertices, axis, minPoly, maxPoly);
			ProjectCircleOntoAxis(m_Center, m_Radius, axis, minCircle, maxCircle);

			float overlap = min(maxPoly, maxCircle) - max(minPoly, minCircle);

			if (overlap <= 0)
			{
				return false; // 重なっていない場合
			}

			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				minAxis = axis;
			}
		}

		// 最小押し出しベクトルの正規化
		if (minAxis.length() > 1e-6f) {
			minAxis.normalize();
			mtv = minAxis * minOverlap;
			mtv *= -0.8f;
		}

		return true;

	}


}
