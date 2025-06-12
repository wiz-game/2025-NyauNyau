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

		//ptrColl->SetMakedSize(2.5f);

		m_Center = Vec3(1.2f, 0.6f, 0.3f);
		Vec3 position = Vec3(m_Center.x, m_Center.y, 0.0f);

		//当たり判定のサイズ
		m_Radius = m_Scale.y/2;

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
		// 半径はスケールの半分
		m_Radius = m_Scale.x / 2.0f;


		if (m_OtherPolygon)
		{
			// 1. 影の頂点をワールド座標に変換
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

				//速度を補正する
				Vec3 collisionNormal = mtv;
				collisionNormal.normalize();

				//上向きの反発（地面）を受けたら
				if (collisionNormal.y > 0.7f)
				{
					m_velocity.y = 0; // Y速度をリセット
					m_isAir = false;  // 地上にいる
				}
				// 横向きの反発（壁）を受けたら
				if (abs(collisionNormal.x) > 0.7f)
				{
					m_velocity.x = 0; // X速度をリセット
				}
			}
		}

		// 絶対座標での地面処理（保険）
		if (currentPosition.y < -4.99f) {
			currentPosition.y = -4.99f;
			m_velocity.y = 0;
			m_isAir = false;
		}


		//最終的な位置をTransformに設定 
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
			// 重力の適用
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_velocity.y += m_gravity * elapsedTime;
			//pos.y += m_velocity.y * elapsedTime;
			auto ptrGra = AddComponent<Gravity>();
			m_isAir = false;


			// 地面との衝突時の処理
			//if (pos.y <= -4.99f)
			//{
			//	m_velocity.y = 0.0f; // 速度をリセット
			//	m_isAir = true; // 空中状態をリセット
			//}



			ptrTransform->SetPosition(pos);

		}
	}

	//Aボタン
	void Player::OnPushA()
	{
		auto pos = GetComponent<Transform>()->GetPosition();

		//if (pos.y == 0.502f || pos.y == 0.501f)
		//{
		//}


		if (m_isAir == false)
		{
			m_velocity.y = 8.0f; // ジャンプの初速を与える
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

	bool Player::ComputeMTV(const std::vector<Vec3>& polygonVertices, Vec3& mtv)
	{
		// ポリゴンに辺がなければ（頂点が2つ未満なら）判定不能
		if (polygonVertices.size() < 2) {
			return false;
		}

		// === ステップ1: ポリゴンの外周上で、円の中心に最も近い点(closestPointOnPolygon)を探す ===
		Vec3 closestPointOnPolygon;
		float minDistanceSq = FLT_MAX; // 最小距離の「2乗」を記録する変数

		for (size_t i = 0; i < polygonVertices.size(); ++i)
		{
			Vec3 p1 = polygonVertices[i];
			Vec3 p2 = polygonVertices[(i + 1) % polygonVertices.size()]; // 次の頂点（リストの最後は最初に戻る）

			// 現在調べている辺のベクトル
			Vec3 edge = p2 - p1;

			// 辺の始点p1から円の中心m_Centerへのベクトル
			Vec3 vecToCenter = m_Center - p1;

			// 辺ベクトルがゼロベクトルでないことを確認
			float edgeLengthSq = edge.dot(edge);
			if (edgeLengthSq < 1e-9f) {
				continue; // この辺は長さがないのでスキップ
			}

			// 円の中心が、辺p1-p2のどの位置に射影されるかを計算 (0.0～1.0の比率t)
			float t = vecToCenter.dot(edge) / edgeLengthSq;

			// tを0.0から1.0の範囲にクランプ（制限）する
			// これにより、最近傍点が必ず辺の上（両端の頂点を含む）に限定される
			if (t > 1.0f) {
				t = 1.0f;
			}
			if (t < 0.0f) {
				t = 0.0f;
			};

			// 辺上での最も近い点を計算
			Vec3 closestPointOnEdge = p1 + edge * t;

			// その点と円の中心との距離（の2乗）を計算
			float distSq = (m_Center - closestPointOnEdge).dot(m_Center - closestPointOnEdge);

			// 今までの最短記録よりも近ければ、記録を更新
			if (distSq < minDistanceSq)
			{
				minDistanceSq = distSq;
				closestPointOnPolygon = closestPointOnEdge;
			}
		}

		// === ステップ2: 衝突しているか判定 ===
		// 円の中心とポリゴン上の最近傍点との距離が、円の半径より大きいか？
		if (minDistanceSq >= m_Radius * m_Radius)
		{
			// 離れている、またはちょうど接している -> 衝突していない
			mtv = Vec3(0.0f, 0.0f, 0.0f);
			return false;
		}

		// --- ここからは衝突していることが確定 ---

		// === ステップ3: 押し出しベクトル(MTV)を計算 ===

		// 押し出す方向は、ポリゴン上の最近傍点から円の中心へ向かう方向
		Vec3 pushDirection = m_Center - closestPointOnPolygon;

		// もし中心点が完全に重なっているなど、ゼロベクトルになったら、仮の押し出し方向（上向きなど）を使う
		if (pushDirection.dot(pushDirection) < 1e-9f) {
			pushDirection = Vec3(0.0f, 1.0f, 0.0f);
		}
		else {
			pushDirection.normalize();
		}

		// 押し出す量は、半径と実際の距離の差
		float overlap = m_Radius - sqrt(minDistanceSq);

		// 最終的なMTVを計算
		mtv = pushDirection * overlap;

		return true; // 衝突したことを伝える
	}
}
