
/*!
@file BoX.cpp
@brief 箱のオブジェクト
*/

#include "stdafx.h"
#include "Project.h"
#include "ShadowComponent.h"
#include "BoxShadowStrategy.h"

namespace basecross
{
	void Box::OnCreate()
	{
		//3Dモデルの呼び出し
		InitDrawComp();

		//トランスフォームコンポーネント取得と設定
		m_transComp = GetComponent<Transform>();
		m_transComp->SetScale(m_Scale);
		m_transComp->SetRotation(m_Rotation);
		m_transComp->SetPosition(m_Position);
		/*m_transComp->SetScale(2.5f, 2.5f, 2.5f);
		m_transComp->SetRotation(0,0,0);
		m_transComp->SetPosition(0.0f, - 4.75f, -4.0f);*/

		//m_transComp->SetScale(2.5, 2.5f, 2.5f);
		//m_transComp->SetPosition(Vec3(10.0f, 11.5f, -20.0f));

		//コリジョンつける
		auto ptrColl = AddComponent<CollisionRect>();
		ptrColl->SetFixed(true);

		/*auto stage = GetStage();
		auto shadowStrategy = std::make_shared<basecross::BoxShadowStrategy>(stage);
		AddComponent<ShadowComponent>(shadowStrategy);*/

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		//ptrString->SetTextRect(Rect2D<float>(16.0f, 240.0f, 640.0f, 480.0f));
	}

	void Box::OnUpdate()
	{

		MoveXZ();
		BoxMove();
		DrawStrings();
	}

	Vec2 Box::GetInputState() const 
	{
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

			auto& app = App::GetApp();
			auto scene = app->GetScene<Scene>();

			wstring log = scene->GetDebugString();
			wstringstream wss;
			wss << log;
	}

	Vec3 Box::GetMoveVector() const
	{
		Vec3 angle(0, 0, 0);
		//入力の取得
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;

		if (moveX != 0 || moveZ != 0)
		{
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();

			// プレイヤーの回転角を考慮
			//float playerRotationY = XMConvertToRadians(m_Rotation.y);


			auto pos = ptrTransform->GetPosition();
			// カメラ方向からの角度
			auto front = pos - ptrCamera->GetEye();
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
			angle *= -moveVec.length();

			//y軸を固定
			angle.y = 0;

			//if (angle.z = 0.0f)
			//{
			//	angle.z += 0.0f;
			//}

			//if (pos.x >= 1.0f)
			//{
			//	angle.z = 0.0f;
			//}
			//else if (pos.z >= 1.0f)
			//{
			//	angle.x = 0.0f;
			//}



		}
		return angle;

		static float direction = 1.0f; // **関数内で値を保持**
		float speed = 1.0f; // 移動速度
		float minX = -3.0f; // 左限界
		float maxZ = 3.0f; // 右限界

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = m_transComp->GetPosition();

		float deltaZ = elapsedTime * speed * direction;

		// 境界チェックして方向反転
		if (pos.z + deltaZ >= maxZ)
		{
			direction = -1.0f; // 方向反転
			pos.z = maxZ; // 境界を超えないようにする
		}

		else if (pos.z + deltaZ <= minX)
		{
			direction = 1.0f; // 方向反転
			pos.z = minX; // 境界を超えないようにする
		}

		else
		{
			pos.z += deltaZ; // 通常の移動
		}

		m_transComp->SetPosition(pos);
		
	}

	void Box::SetSelectedForControl(bool selected) 
	{
		m_isSelectedForControl = selected;
	}

	bool Box::IsSelectedForControl() const 
	{
		return m_isSelectedForControl;
	}

	void Box::MoveXZ() 
	{
		if (!IsSelectedForControl()) 
		{
			return;
		}

		auto angle = GetInputState();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = GetComponent<Transform>()->GetPosition();
		pos += elapsedTime * m_velocity;
		GetComponent<Transform>()->SetPosition(pos);
	}

	void Box::BoxMove()
	{		
		// 自分が操作対象として選択されていなければ、移動処理は行わない
		if (!IsSelectedForControl()) 
		{
			return;
		}

		float elapsedTime = App::GetApp()->GetElapsedTime();
		//auto angle = GetMoveVector();
		//if (angle.length() > 0.0f)
		//{
		//	auto pos = GetComponent<Transform>()->GetPosition();
		//	pos += angle * elapsedTime * 6.0f;
		//	GetComponent<Transform>()->SetPosition(pos); // 更新後
		//}

		Vec3 moveDirection = GetMoveVector(); // スティック入力から移動方向を取得

		if (moveDirection.length() > 0.0f)
		{
			auto currentTransform = GetComponent<Transform>();
			Vec3 currentPos = currentTransform->GetPosition(); // Boxのポジション
			Vec3 boxScaleHalved = currentTransform->GetScale() / 2.0f; // Box自身のサイズの半分

			// 移動量を計算
			Vec3 deltaMove = moveDirection * elapsedTime * 6.0f; // 6.0f は移動スピード
			Vec3 nextPos = currentPos + deltaMove; //Boxのポジションに移動の値を足す

			// --- テーブルの範囲情報を取得 ---
			auto stage = GetStage();

			auto stageptr = dynamic_pointer_cast<GameStage>(stage);
			auto stageptr2 = dynamic_pointer_cast<GameStage2>(stage);

			if (stageptr) 
			{
				auto table = stageptr->GetTableObject(); // GameStageからTableオブジェクトを取得
				if (table) 
				{
					auto tableTransform = table->GetComponent<Transform>();
					Vec3 tablePos = tableTransform->GetPosition();   // テーブルの位置
					Vec3 tableScale = tableTransform->GetScale();    // テーブルのスケール

					// スケール補正係数 (例: 見た目が10倍なら10.0f)
					float scaleCorrectionFactor = 10.0f;
					Vec3 actualTableScale = tableScale * scaleCorrectionFactor; //テーブルのスケールが小さいため、スケールに値をかけて大きく設定する

					// テーブルのX方向の範囲を計算
					float tableMinX = tablePos.x - actualTableScale.x / 2.0f; //テーブルの左端限界
					float tableMaxX = tablePos.x + actualTableScale.x / 2.0f; //テーブルの右端限界
					// テーブルのZ方向の範囲を計算
					float tableMinZ = tablePos.z - (actualTableScale.z - 4.0f) / 2.0f; //テーブルの手前限界
					float tableMaxZ = tablePos.z + (actualTableScale.z + 4.0f)/ 2.0f; //テーブルの奥行限界

					// --- Boxの新しいX座標をテーブルの範囲内に制限 ---
				    // Boxの左端がテーブルの左端より内側の場合
					if (nextPos.x - boxScaleHalved.x < tableMinX) 
					{
						nextPos.x = tableMinX + boxScaleHalved.x; //Boxの位置をテーブルの左端限界にBoxのサイズの半分の値を足した値の場所にする(押し出し)
					}
					// Boxの右端がテーブルの右端より内側の場合
					else if (nextPos.x + boxScaleHalved.x > tableMaxX) 
					{
						nextPos.x = tableMaxX - boxScaleHalved.x; //Boxの位置をテーブルの右端限界にBoxのサイズの半分の値を足した値の場所にする(押し出し)

					}
					// --- Boxの新しいZ座標をテーブルの範囲内に制限 ---
					// Boxの手前側がテーブルの手前側より内側の場合
					if (nextPos.z - boxScaleHalved.z < tableMinZ) 
					{
						nextPos.z = tableMinZ + boxScaleHalved.z; //Boxの位置をテーブルの手前限界にBoxのサイズの半分の値を足した値の場所にする(押し出し)
					}
					// Boxの奥側がテーブルの奥側より内側の場合
					else if (nextPos.z + boxScaleHalved.z > tableMaxZ) 
					{
						nextPos.z = tableMaxZ - boxScaleHalved.z; //Boxの位置をテーブルの奥行限界にBoxのサイズの半分の値を足した値の場所にする(押し出し)
					}
				}
				// --- 制限された新しい位置を適用 ---
				currentTransform->SetPosition(nextPos);
			}

			else if (stageptr2)
			{
				auto table = stageptr2->GetTableObject(); // GameStageからTableオブジェクトを取得
				if (table)
				{
					auto tableTransform = table->GetComponent<Transform>();
					Vec3 tablePos = tableTransform->GetPosition();   // テーブルの位置
					Vec3 tableScale = tableTransform->GetScale();    // テーブルのスケール

					// スケール補正係数 (例: 見た目が10倍なら10.0f)
					float scaleCorrectionFactor = 10.0f;
					Vec3 actualTableScale = tableScale * scaleCorrectionFactor; //テーブルのスケールが小さいため、スケールに値をかけて大きく設定する

					// テーブルのX方向の範囲を計算
					float tableMinX = tablePos.x - actualTableScale.x / 2.0f; //テーブルの左端限界
					float tableMaxX = tablePos.x + actualTableScale.x / 2.0f; //テーブルの右端限界
					// テーブルのZ方向の範囲を計算
					float tableMinZ = tablePos.z - (actualTableScale.z - 4.0f) / 2.0f; //テーブルの手前限界
					float tableMaxZ = tablePos.z + (actualTableScale.z + 4.0f) / 2.0f; //テーブルの奥行限界

					// --- Boxの新しいX座標をテーブルの範囲内に制限 ---
					// Boxの左端がテーブルの左端より内側の場合
					if (nextPos.x - boxScaleHalved.x < tableMinX)
					{
						nextPos.x = tableMinX + boxScaleHalved.x; //Boxの位置をテーブルの左端限界にBoxのサイズの半分の値を足した値の場所にする(押し出し)
					}
					// Boxの右端がテーブルの右端より内側の場合
					else if (nextPos.x + boxScaleHalved.x > tableMaxX)
					{
						nextPos.x = tableMaxX - boxScaleHalved.x; //Boxの位置をテーブルの右端限界にBoxのサイズの半分の値を足した値の場所にする(押し出し)

					}
					// --- Boxの新しいZ座標をテーブルの範囲内に制限 ---
					// Boxの手前側がテーブルの手前側より内側の場合
					if (nextPos.z - boxScaleHalved.z < tableMinZ)
					{
						nextPos.z = tableMinZ + boxScaleHalved.z; //Boxの位置をテーブルの手前限界にBoxのサイズの半分の値を足した値の場所にする(押し出し)
					}
					// Boxの奥側がテーブルの奥側より内側の場合
					else if (nextPos.z + boxScaleHalved.z > tableMaxZ)
					{
						nextPos.z = tableMaxZ - boxScaleHalved.z; //Boxの位置をテーブルの奥行限界にBoxのサイズの半分の値を足した値の場所にする(押し出し)
					}
				}
				// --- 制限された新しい位置を適用 ---
				currentTransform->SetPosition(nextPos);
			}

		}
	}

	std::vector<Vec3> Box::GetBoxVertices() const
	{
		//頂点を返す
		return 
		{
		Vec3(-0.5f, -0.5f, -0.5f),
		Vec3(0.5f, -0.5f, -0.5f),
		Vec3(-0.5f,  0.5f, -0.5f),
		Vec3(0.5f,  0.5f, -0.5f),
		Vec3(-0.5f, -0.5f,  0.5f),
		Vec3(0.5f, -0.5f,  0.5f),
		Vec3(-0.5f,  0.5f,  0.5f),
		Vec3(0.5f,  0.5f,  0.5f)
		};
	}

	void Box::DrawStrings()
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

	void Box::InitDrawComp()
	{
		Mat4x4 span;
		span.affineTransformation
		(
			Vec3(1.0f), 
			Vec3(0.0f, 0.0f, 0.0f), 
			Vec3(0.0f, 0.0f, 0.0f), 
			Vec3(0.0f, -0.0f, 0.0f)
		);

     		m_drawModelComp = AddComponent<PNTBoneModelDraw>();
			m_drawModelComp->SetMeshResource(L"MODEL_TSUMIKI1");

			m_drawModelComp->SetMeshToTransformMatrix(span);


	}

}
//end basecross
