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
		m_isAir(true),
		m_isDead(false),
		m_isFallSE(false),
		m_fallSound(nullptr),
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
		ptrString->SetTextRect(Rect2D<float>(16.0f, 150.0f, 640.0f, 480.0f));



		auto pos = GetComponent<Transform>()->GetPosition();
		auto wall = GetStage()->GetSharedGameObject<Wall>(L"Wall_0");
		Vec3 wallPoint = wall->GetWallPosition();

		pos.z = wallPoint.z;
	}

	void Player::OnUpdate()
	{
		// このフレームの経過時間を取得。すべての時間ベースの計算で使う。
		float elapsedTime = App::GetApp()->GetElapsedTime();

		// ===================================================================
		// === ステップ1: プレイヤーの「意志」と「世界の法則」で速度を更新 ===
		// ===================================================================

		// プレイヤーからの入力を処理系に登録する。
		// これにより、このフレームでAボタンが押されればOnPushAが呼ばれる。
		m_InputHandler.PushHandle(GetThis<Player>());

		// --- 速度ベクトルの各成分を決定 ---

		// X方向：常に一定の速度で右に進み続ける、というゲームのルール。
		m_velocity.x = m_Speed;

		// Y方向：物理法則（重力）を適用する。
		// このm_isAirは、「前のフレームの終わり」に決定された接地状態。
		if (m_isAir)
		{
			// もし空中にいるなら、重力によって落下速度を増加させる。
			m_velocity.y += m_gravity * elapsedTime;
		}
		else
		{
			// もし地面にいるなら、不必要な落下や上昇を防ぐ。
			// (ただし、ジャンプ直後の上昇速度(y>0)は消さないように、下降速度(y<0)だけをリセット)
			if (m_velocity.y < 0) {
				m_velocity.y = 0;
			}
		}

		// =================================================================
		// === ステップ2: 移動と衝突の「シミュレーション」を行う         ===
		// =================================================================

		// 現在位置を取得し、このフレームで動くべき「生の」移動量を計算する。
		auto ptrTransform = GetComponent<Transform>();
		Vec3 currentPosition = ptrTransform->GetPosition();
		Vec3 deltaPosition = m_velocity * elapsedTime;

		// --- 2a. 複数の影との当たり判定ループ ---
		// これから動く先の「未来の位置」で当たり判定を行う（予測ベースの判定）。
		m_Center = currentPosition + deltaPosition;
		// プレイヤーの当たり判定の大きさを、不均一スケールも考慮して決定する。
		m_Radius = ((m_Scale.x < m_Scale.y) ? m_Scale.x : m_Scale.y) / 2.0f;

		// このフレームで最も重要（めり込みが最大）だった衝突情報を記録する変数。
		Vec3 best_mtv(0.0f, 0.0f, 0.0f);
		float max_overlap_sq = 0.0f;

		// シーンから影の管理者である「ShadowDrawer」を探し出す。
		auto shadowDrawer = GetStage()->GetSharedGameObject<ShadowDrawer>(L"ShadowDrawer");
		if (shadowDrawer)
		{
			// ShadowDrawerから、影の計算と描画を統括する「ShadowComponent」を取得。
			auto shadowComp = shadowDrawer->GetComponent<ShadowComponent>();
			if (shadowComp)
			{
				// ShadowComponentが計算した、最新の「すべての影の頂点リスト」をもらう。
				const auto& allShadows = shadowComp->GetAllShadowsVertices();
				// すべての影に対して、当たり判定を試みる。
				for (const auto& singleShadowVertices : allShadows)
				{
					if (singleShadowVertices.size() < 3) continue; // ポリゴンでなければスキップ。

					Vec3 mtv;
					// あなたが完成させた、2Dボロノイ領域ベースの衝突判定を実行。
					if (ComputeMTV(singleShadowVertices, mtv))
					{
						// 衝突した場合、そのめり込み量（の2乗）を計算。
						float current_overlap_sq = mtv.dot(mtv);
						// もし、今回のめり込みが今までの最大記録よりも大きいなら、記録を更新。
						if (current_overlap_sq > max_overlap_sq)
						{
							max_overlap_sq = current_overlap_sq;
							best_mtv = mtv; // この衝突を「最も重要な衝突」として記憶する。
						}
					}
				}
			}
		}

		// =================================================================
		// === ステップ3: シミュレーション結果に基づき、物理状態を補正する ===
		// =================================================================

		// best_mtvが更新されていれば（ゼロベクトルでなければ）、何らかの衝突があったと判断。
		if (best_mtv.dot(best_mtv) > 1e-9f)
		{
			// --- 3a. 位置の補正 ---
			// まず、最も深刻なめり込み(best_mtv)を使って、現在の位置を押し戻す。
			// これで、過去のフレームから持ち越した、わずかなめり込みが解消される。
			currentPosition += best_mtv;

			// --- 3b. 速度の補正 ---
			// 次に、未来のフレームで同じめり込みが起きないように、速度ベクトルを補正する。
			Vec3 collisionNormal = best_mtv.normalize();
			float dot_vel_norm = m_velocity.dot(collisionNormal);

			// 速度が衝突面にめり込む方向を向いている（内積が負）場合のみ補正。
			if (dot_vel_norm < 0) {
				// 速度ベクトルから、衝突面に垂直な（めり込む）成分を完全に除去する。
				// これにより、プレイヤーは壁に「ピタッ」と止まる。
				m_velocity -= collisionNormal * dot_vel_norm;
			}

			// --- 3c. 接地状態の決定 ---
			// 衝突面の法線の向きと、プレイヤーのY速度から、本当に「接地」したかを厳密に判断。
			if (collisionNormal.y > 0.7f && m_velocity.y <= 0.0f) {
				// 歩ける斜面、かつ落下中なら、接地とみなす。
				m_isAir = false;
				m_velocity.y = 0; // 接地したので、Y速度を確実にゼロにリセット。
			}
			else {
				// それ以外（横壁や、駆け上がっている坂など）との衝突なら、まだ空中扱い。
				m_isAir = true;
			}
		}
		else // どの影とも衝突しなかった場合
		{
			// 何にも当たらなければ、当然、空中にいる。
			m_isAir = true;
		}

		// =================================================================
		// === ステップ4: 最終的な位置を決定し、Transformに適用する      ===
		// =================================================================

		// 衝突応答によって補正された「後」の、安全な速度で、最終的な移動量を再計算。
		deltaPosition = m_velocity * elapsedTime;

		// 最下層の床に落ちないようにする、最後の安全装置。
		if ((currentPosition.y + deltaPosition.y) < -4.99f) {
			deltaPosition.y = -4.99f - currentPosition.y;
			m_velocity.y = 0;
			m_isAir = false;
		}

		// 「補正済みの現在位置」に、「補正済みの移動量」を加えて、最終的な位置をセットする。
		ptrTransform->SetPosition(currentPosition + deltaPosition);

		// デバッグ用の文字列を描画。
		DrawStrings();
	}


	void Player::MoveXZ() 
	{
		/*auto angle = GetInputState();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = GetComponent<Transform>()->GetPosition();
		pos += elapsedTime * m_velocity;
		GetComponent<Transform>()->SetPosition(pos);*/
	}

	void Player::MoveY() 
	{
		//auto ptrTransform = GetComponent<Transform>();
		//auto pos = GetComponent<Transform>()->GetPosition();


		//if (m_isAir == true)
		//{
		//	// 重力の適用
		//	float elapsedTime = App::GetApp()->GetElapsedTime();
		//	//m_velocity.y += m_gravity * elapsedTime;
		//	auto ptrGra = AddComponent<Gravity>();

		//	ptrTransform->SetPosition(pos);

		//}
	}

	//Aボタン
	void Player::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto volume = scene->m_volumeBGM;
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		auto volumeSE = scene->m_volumeSE;

		if (m_isAir == false)
		{
			m_velocity.y = 4.0f; // ジャンプの初速を与える
			m_isAir = true; // ジャンプしたので空中状態にする
			ptrXA->Start(L"Jump", 0, volumeSE);

		}
		else
		{
			auto ptrTransform = GetComponent<Transform>();
			auto pos = GetComponent<Transform>()->GetPosition();

			//重力の適用
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_velocity.y += elapsedTime;
			auto ptrGra = AddComponent<Gravity>();

			ptrTransform->SetPosition(pos);
		}

	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other)
	{
		//すでに死亡中なら何もしない
		if (m_isDead)
		{
			return;
		}

		// 衝突対象が地面または敵か確認
		if (dynamic_pointer_cast<Ground>(Other) || dynamic_pointer_cast<Enemy>(Other))
		{
			auto scene = App::GetApp()->GetScene<Scene>();
			auto volumeBGM = scene->m_volumeBGM;
			auto volumeSE = scene->m_volumeSE;

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Stop(m_fallSound);
			m_fallSound = nullptr;

			ptrXA->Start(L"Fall", 0, volumeSE);
			m_isDead = true;

			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToGameOverStage");
			// 自分が所属しているステージ（GameStage）のポインタを取得
		//	auto stage = std::dynamic_pointer_cast<GameStage>(GetStage());
		//	if (stage) {
		//		// GameStageにゲームオーバー処理の開始を依頼する
		//		stage->StartGameOver();
		//	}
		}

		else if (dynamic_pointer_cast<ShadowFloor>(Other) || dynamic_pointer_cast<BookShelf>(Other))
		{
			m_velocity.y *= 0;
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
		mtv = Vec3(mtv2D.x, mtv2D.y+0.025, 0.0f);

		return true;
	}
}
