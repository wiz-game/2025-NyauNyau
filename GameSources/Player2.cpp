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
		m_Radius = 0.1f;

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
		auto G = GetStage()->GetThis<GameStage>()->GetGameObjectVec();
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		MovePlayer();
		//DrawStrings();
		MoveY();
		MoveXZ();

		auto& app = App::GetApp();
		auto ptrTransform = GetComponent<Transform>(); // OnCreateでキャッシュしたm_Transformを使ってもOK
		Vec3 currentPlayerPosition = ptrTransform->GetPosition();
		float elapsed = app->GetElapsedTime();
		float gravity = 0.0f;
		Vec3 acceleration = Vec3(0.0f, -gravity, 0.0f) * elapsed;
		static Vec3 velocity = Vec3();
		velocity += acceleration * elapsed;

		Vec3 position2D = GetCenter() + velocity * elapsed;
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
			// 影の頂点をワールド座標に変換
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

			// 衝突判定を実行
			Vec3 mtv;
			if (ComputeMTV(worldVertices, mtv))
			{
				currentPosition += mtv*1.01; // めり込んだ分を押し戻す

				// 速度を補正する
				Vec3 collisionNormal = mtv;
				collisionNormal.normalize();

				// もし、上向きの反発（地面からの反発）を受けたら
				if (collisionNormal.y > 0.7f)
				{
					m_velocity.y = 0;
					m_isAir = false; // ★地面にいるのでfalse
				}
				else
				{
					// 地面から離れた瞬間
					m_isAir = true; // 地面にいないのでtrue
				}

				// === すべての計算が終わった最終的な位置をTransformに設定 ===
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

	//mtv⇐押し出しのベクトル
	bool Player::ComputeMTV(const std::vector<Vec3>& polygonVertices, Vec3& mtv)
		//bool Player::ComputeMTV(const shared_ptr<ShadowObject>& polygon, const Vec3& sphereWorldCenter, float sphereRadius, Vec3& mtv)// 変更後
	{
		// === 変数の初期化 ===
		//vector<Vec3> polygonVertices = polygonVertices->GetVertices();
		if (polygonVertices.empty()) {
			return false; // ポリゴンに頂点がなければ判定不能
		}

		float minOverlap = FLT_MAX; // C++でfloatの最大値 (cfloatヘッダ)
		Vec3 smallestAxis;          // 最小の重なりを生んだ軸を保存する変数

		std::vector<Vec3> axes;     // テストすべき軸をすべて入れるリスト


		// === 分離軸の候補をすべて集める ===

		// 2a. ポリゴンの「辺の法線」をすべてリスト(axes)に追加
		for (size_t i = 0; i < polygonVertices.size(); ++i) {
			Vec3 p1 = polygonVertices[i];
			Vec3 p2 = polygonVertices[(i + 1) % polygonVertices.size()];
			Vec3 normal = GetNormal(p1, p2); // 事前に修正した2D法線関数を想定
			if (normal.length() > 1e-6f) { // ゼロベクトルでなければ追加
				axes.push_back(normal);
			}
		}

		// 2b. 円の中心に「最も近い頂点へのベクトル」をリスト(axes)に追加
		Vec3 closestVertex;
		float minDistanceSq = FLT_MAX;
		for (const auto& vertex : polygonVertices) {
			// 距離の「2乗」で比較する (高速)
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


		// ===  集めた軸で、一つずつ判定を行う ===
		for (const auto& axis : axes) {
			float minPoly, maxPoly, minCircle, maxCircle;
			ProjectOntoAxis(polygonVertices, axis, minPoly, maxPoly);
			ProjectCircleOntoAxis(m_Center, m_Radius, axis, minCircle, maxCircle);

			float overlap = min(maxPoly, maxCircle) - max(minPoly, minCircle);

			if (overlap <= 0.0f) {
				// 分離軸が見つかった！ 即座に「衝突していない」と判断して終了
				mtv = Vec3(0.0f, 0.0f, 0.0f);
				return false;
			}

			// 最小の重なり記録を更新する
			if (overlap < minOverlap) {
				minOverlap = overlap;
				smallestAxis = axis;
			}
		}

		// === 最終的な押し出しベクトル(MTV)を計算 ===
		// この時点ですべての軸で重なりがあったので、衝突が確定している

		// 押し出しベクトルを計算
		mtv = smallestAxis * minOverlap;

		// MTVの方向を正しくする
		// 円の中心からポリゴンの中心へのベクトルを計算
		Vec3 polyCenter(0.0f, 0.0f, 0.0f);
		for (const auto& v : polygonVertices) polyCenter += v;
		polyCenter /= static_cast<float>(polygonVertices.size());

		// 円からポリゴンへ向かう方向と、現在のmtvの方向が逆なら、mtvを反転させる
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


		return true; // 衝突したことを伝える


		//return true;
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();


		wstring log = scene->GetDebugString();
		wstringstream wss;
		wss << log;

		wss << polygonVertices.size();
	}
}
