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
		m_isAir(true),
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

			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();

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

			//if (m_Player1)
			//{
				//z軸を固定
				angle.z = 0;
			//}
			//else
			//{
			//	//x軸を固定
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

		// x方向に自動移動
		pos.x += elapsedTime * m_Speed;


		GetComponent<Transform>()->SetPosition(pos); // 更新後

	}

	void Player::Jump(shared_ptr<GameObject>& jump)
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		auto pos = GetComponent<Transform>()->GetPosition();
		//重力をつける
		auto ptrGra = AddComponent<Gravity>();

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
		//ptrColl->SetMakedSize(2.5f);

		m_Center = Vec3(1.2f, 0.6f, 0.3f);
		Vec3 position = Vec3(m_Center.x, m_Center.y, 0.0f);

		

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_SQUARE");
		ptrDraw->SetTextureResource(L"TEX_NEZUMI2");
		//ptrDraw->SetTextureResource(L"TEX_NEZUMI");


		SetAlphaActive(true);


		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));



		auto pos = GetComponent<Transform>()->GetPosition();
		auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
		Vec3 wallPoint = wall->GetWallPosition();

		pos.z = wallPoint.z;

		auto objects = GetStage()->GetGameObjectVec();

		for (auto& obj : objects) {
			auto result = dynamic_pointer_cast<ShadowObject>(obj);

			if (result) {
				m_OtherPolygon = result;
				break;
			}
		}
	}


	void Player::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();

		//入力と重力に基づいて、このフレームの速度(m_velocity)を決定する
		m_InputHandler.PushHandle(GetThis<Player>()); // ジャンプ入力(OnPushA)の受付

		// X方向の移動速度（自動で右に進む）
		m_velocity.x = m_Speed;

		// Y方向の移動速度（常に重力を適用する）
		// 地面にいるかどうかは、この後の衝突判定で判断する
		m_velocity.y += m_gravity * elapsedTime;
		m_isAir = true; // 基本的に空中にいると仮定し、地面にいたら後でfalseにする
		MoveY();

		//速度に基づいて、プレイヤーを「仮に」移動させる
		auto ptrTransform = GetComponent<Transform>();
		Vec3 currentPosition = ptrTransform->GetPosition();
		currentPosition += m_velocity * elapsedTime;


		//衝突判定と応答

		// 判定に使う円の中心は、移動後のプレイヤーの位置そのもの
		m_Center = currentPosition;

		// 半径はスケールの半分(少し大きめにする)
		m_Radius = m_Scale.x / 2.0f;

		if (m_OtherPolygon)
		{
			//影の頂点をワールド座標に変換
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

			//衝突判定を実行
			Vec3 mtv;
			if (ComputeMTV(worldVertices, mtv))
			{
				// --- 衝突した場合の補正処理 ---

				//位置を補正する（1%多めに押し出す）
				currentPosition += mtv * 1.01f;

				// 3b. 速度を補正する（★ここをより強力なロジックに修正★）
				Vec3 collisionNormal = mtv;
				collisionNormal.normalize();

				// 現在の速度と、衝突面の法線の内積を計算
				float dot_vel_norm = m_velocity.dot(collisionNormal);

				// もし、速度が衝突面にめり込む方向（内積が負）を向いているなら...
				if (dot_vel_norm < 0)
				{
					// 法線方向の速度成分を、完全に打ち消すベクトルを計算
					Vec3 reflectionVector = collisionNormal * dot_vel_norm;

					// 現在の速度に、その打ち消しベクトルを加算する
					// これにより、壁にめり込む方向の速度がゼロになる
					m_velocity += reflectionVector;
				}

				m_velocity.y = 0;
				m_isAir = false;

				// 地面との接触判定（これは重要なので残す）
				if (collisionNormal.y > 0.7f)
				{
					m_isAir = false;
				}
			}
		}

		//最終的な位置をTransformに設定 
		ptrTransform->SetPosition(currentPosition);

		// 絶対座標での地面処理（保険）
		if (currentPosition.y < -4.99f) {
			currentPosition.y = -4.99f;
			m_velocity.y = 0;
			m_isAir = false;
		}
		DrawStrings();
	}


	void Player::MoveXZ() 
	{
		auto angle = GetInputState();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = GetComponent<Transform>()->GetPosition();
		pos += elapsedTime * m_velocity;
		GetComponent<Transform>()->SetPosition(pos);
	}


	void Player::MoveY() 
	{
		auto ptrTransform = GetComponent<Transform>();
		auto pos = GetComponent<Transform>()->GetPosition();


		if (m_isAir == true)
		{
			// 重力の適用
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_velocity.y += m_gravity * elapsedTime;
			auto ptrGra = AddComponent<Gravity>();

			ptrTransform->SetPosition(pos);

		}
	}

	//Aボタン
	void Player::OnPushA()
	{
		auto pos = GetComponent<Transform>()->GetPosition();

		if (m_isAir == false)
		{
			m_velocity.y = 10.0f; // ジャンプの初速を与える
			m_isAir = true; // ジャンプしたので空中状態にする
		}

	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other)
	{
	    if (dynamic_pointer_cast<Ground>(Other)) // 衝突対象が地面か確認
		{
			m_velocity.y = 0;
			m_isAir = false;
			//m_collisionFlag = true;

			auto scene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToGameOverStage");
		}
		else if (dynamic_pointer_cast<ShadowFloor>(Other))
		{
			m_velocity.y = 0;
			m_isAir = false;

		}
	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		//m_collisionFlag = false;
	}


	//void Player::SetPlayerMove(bool Player1)
	//{
	//	m_Player1 = Player1;
	//}

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

	//mtv⇐押し出しのベクトル
	bool Player::ComputeMTV(const std::vector<Vec3>& polygonVertices, Vec3& mtv)
	{
		if (polygonVertices.size() < 2) {
			return false;
		}

		// ★★★ 判定に使う円の中心を2Dに変換 ★★★
		Vec2 center2D(m_Center.x, m_Center.y);
		float radiusSq = m_Radius * m_Radius;

		// === ステップ1: ポリゴン上の最近傍点を2Dで探す ===
		Vec2 closestPointOnPolygon2D;
		float minDistanceSq = FLT_MAX;

		for (size_t i = 0; i < polygonVertices.size(); ++i)
		{
			// ★★★ 頂点も2Dに変換 ★★★
			Vec2 p1(polygonVertices[i].x, polygonVertices[i].y);
			Vec2 p2(polygonVertices[(i + 1) % polygonVertices.size()].x, polygonVertices[(i + 1) % polygonVertices.size()].y);

			Vec2 edge = p2 - p1;
			Vec2 vecToCenter = center2D - p1;

			float edgeLengthSq = edge.dot(edge);
			if (edgeLengthSq < 1e-9f) {
				continue;
			}

			float t = vecToCenter.dot(edge) / edgeLengthSq;
			// もしtが1.0を超えていたら、1.0に制限する
			if (t > 1.0f) {
				t = 1.0f;
			}
			// もしtが0.0未満だったら、0.0に制限する
			else if (t < 0.0f) {
				t = 0.0f;
			}

			Vec2 closestPointOnEdge = p1 + edge * t;
			float distSq = (center2D - closestPointOnEdge).dot(center2D - closestPointOnEdge);

			if (distSq < minDistanceSq)
			{
				minDistanceSq = distSq;
				closestPointOnPolygon2D = closestPointOnEdge;
			}
		}

		// === ステップ2: 2Dで衝突判定 ===
		if (minDistanceSq >= radiusSq)
		{
			mtv = Vec3(0.0f, 0.0f, 0.0f);
			return false;
		}

		// === ステップ3: MTVを2Dで計算し、3Dベクトルに戻す ===
		Vec2 pushDirection2D = center2D - closestPointOnPolygon2D;
		if (pushDirection2D.dot(pushDirection2D) < 1e-9f) {
			// もし中心が重なったら、仮に上向きに押し出す
			pushDirection2D = Vec2(0.0f, 1.0f);
		}
		else {
			pushDirection2D.normalize();
		}

		float overlap = m_Radius - sqrt(minDistanceSq);

		// ★★★ 2Dの押し出しベクトルを計算 ★★★
		Vec2 mtv2D = pushDirection2D * overlap;

		// ★★★ 3Dベクトルに戻す（Z成分は必ず0） ★★★
		mtv = Vec3(mtv2D.x, mtv2D.y, 0.0f);

		return true;
	}
}
