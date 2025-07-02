#include "stdafx.h"
#include "Project.h"
#include "ShadowDrawer.h"


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
		m_Speed(8.0f),
		m_isAir(false),
		m_Player1(false),
		m_cameraAngleY(0.0f),
		m_forward(0.0f),
		m_velocityY(0.0f),
		m_velocity(0.0f),
		m_collisionFlag(false),
		m_gravity(-4.0),
		m_Radius(0.0f),
		m_Center(0.0f, 0.0f, 0.0f),
		m_jumpBufferCounter(0.0f),
		m_isDead(false),
		m_isFallSE(false),
		m_number(0)
	{
	}

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
		ptrColl->SetMakedSize(1);

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
		ptrString->SetTextRect(Rect2D<float>(16.0f, 150.0f, 640.0f, 480.0f));

		auto pos = GetComponent<Transform>()->GetPosition();
		auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
		Vec3 wallPoint = wall->GetWallPosition();

		pos.z = wallPoint.z;
	}

	void Player::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_InputHandler.PushHandle(GetThis<Player>()); // ジャンプ入力はいつでも受け付ける

		auto ptrTransform = GetComponent<Transform>();
		Vec3 currentPosition = ptrTransform->GetPosition();

		//このフレームで働く力をすべて速度に反映
		m_velocity.x = m_Speed;
		//接地していなくても、まず重力を計算する
		m_velocity.y += m_gravity * elapsedTime;


		//速度から、このフレームの移動量を計算
		Vec3 deltaPosition = m_velocity * elapsedTime;


		//衝突判定と、それに基づく「状態の確定」と「補正」

		//判定用の中心と半径を設定
		m_Center = currentPosition + deltaPosition; 
		m_Radius = ((m_Scale.x < m_Scale.y) ? m_Scale.x : m_Scale.y) / 2.0f;

		//複数当たり判定ループで、最も深刻な衝突(best_mtv)を見つける
		Vec3 best_mtv(0, 0, 0);
		float max_overlap_sq = 0.0f;

		auto shadowDrawer = GetStage()->GetSharedGameObject<ShadowDrawer>(L"ShadowDrawer");
		//ShadowDrawerの判定
		if (shadowDrawer) {
			//ShadowComponentがあったらやる
			auto shadowComp = shadowDrawer->GetComponent<ShadowComponent>();
			if (shadowComp) {
				//判定の処理
				const auto& allShadows = shadowComp->GetAllShadowsVertices();
				for (const auto& singleShadowVertices : allShadows) {
					if (singleShadowVertices.size() < 3) continue;
					Vec3 mtv;
					if (ComputeMTV(singleShadowVertices, mtv)) {
						float current_overlap_sq = mtv.dot(mtv);
						if (current_overlap_sq > max_overlap_sq) {
							max_overlap_sq = current_overlap_sq;
							best_mtv = mtv;
						}
					}
				}
			}
		}

		//衝突応答
		if (best_mtv.dot(best_mtv) > 1e-9f) // 衝突があったか？
		{
			// まず、位置を押し出して補正する
			deltaPosition += best_mtv * 1.01f;

			Vec3 collisionNormal = best_mtv.normalize();

			// 条件：地面に、めり込むように接触したか
			if (collisionNormal.y > 0.7f && m_velocity.y <= 0)
			{
				m_velocity.y = 0;
			}

			// 横壁に当たった場合も同様に、X速度をゼロにする
			if (abs(collisionNormal.x) > 0.7f && m_velocity.x != 0)
			{
				m_velocity.x = 0;
			}
		}

		//最終的な位置を適用
		deltaPosition = m_velocity * elapsedTime;
		if (abs(m_velocity.y) < 0.1f) { // わずかな誤差を許容
			m_isAir = false;
		}
		else {
			m_isAir = true;
		}

		//層地面処理
		/*if((currentPosition.y + deltaPosition.y) < -4.99f) {
			deltaPosition.y = -4.99f - currentPosition.y;
			m_velocity.y = 0;
			m_isAir = false;
		}*/

		ptrTransform->SetPosition(currentPosition + deltaPosition);
		DrawStrings();
	}

	//Aボタン
	void Player::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto volume = scene->m_volumeBGM;
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		m_jumpBufferCounter = 0.15f;

		if (m_isAir == false)
		{
			m_velocity.y = 3.0f; // ジャンプの初速を与える
			m_isAir = true; // ジャンプしたので空中状態にする
			ptrXA->Start(L"Jump", 0, 0.5f);

		}
		else
		{
			auto ptrTransform = GetComponent<Transform>();
			auto pos = GetComponent<Transform>()->GetPosition();

			//重力の適用
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_velocity.y += elapsedTime;

			ptrTransform->SetPosition(pos);
		}

	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& Other)
	{
		
	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& Other)
	{
		//m_collisionFlag = false;
	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		if (dynamic_pointer_cast<Ground>(Other)) // 衝突対象が地面か確認
		{
			auto scene = App::GetApp()->GetScene<Scene>();

			auto volume = scene->m_volumeBGM;

			auto ptrXA = App::GetApp()->GetXAudio2Manager();

			ptrXA->Start(L"Fall", 0, 0.5f);

			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToGameOverStage");
		}

		else if (dynamic_pointer_cast<ShadowFloor>(Other) || dynamic_pointer_cast<BookShelf>(Other))
		{
			m_velocity.y = 0;
			m_isAir = false;

		}
	}

	//void Player::SetPlayerMove(bool Player1)
	//{
	//	m_Player1 = Player1;
	//}

	void Player::DrawStrings()
	{
		//auto pos = GetComponent<Transform>()->GetPosition();
		Mat4x4 worldPos = GetComponent<Transform>()->GetWorldMatrix();
		Vec3 pos = Vec3(worldPos._41, worldPos._42, worldPos._43);
		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, 12, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, 12, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, 12, Util::FloatModify::Fixed) + L"\n";
		positionStr += L"m_isAir" + Util::FloatToWStr(m_isAir, 12, Util::FloatModify::Fixed) + L"\n";

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

		//判定に使う円の中心を2Dに変換
		Vec2 center2D(m_Center.x, m_Center.y);
		float radiusSq = m_Radius * m_Radius;

		// === ポリゴン上の最近傍点を2Dで探す ===
		Vec2 closestPointOnPolygon2D;
		float minDistanceSq = FLT_MAX;

		for (size_t i = 0; i < polygonVertices.size(); ++i)
		{
			//頂点も2Dに変換
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

		// === 2Dで衝突判定 ===
		if (minDistanceSq >= radiusSq)
		{
			mtv = Vec3(0.0f, 0.0f, 0.0f);
			return false;
		}

		// ===  MTVを2Dで計算し、3Dベクトルに戻す ===
		Vec2 pushDirection2D = center2D - closestPointOnPolygon2D;
		if (pushDirection2D.dot(pushDirection2D) < 1e-9f) {
			// もし中心が重なったら、仮に上向きに押し出す
			pushDirection2D = Vec2(0.0f, 1.0f);
		}
		else {
			pushDirection2D.normalize();
		}

		float overlap = m_Radius - sqrt(minDistanceSq);

		// 2Dの押し出しベクトルを計算
		Vec2 mtv2D = pushDirection2D * overlap;

		//3Dベクトルに戻す（Z成分は必ず0
		mtv = Vec3(mtv2D.x, mtv2D.y + 0.025, 0.0f);

		return true;
	}
}
