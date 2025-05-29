
/*!
@file BoX.cpp
@brief 箱のオブジェクト
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{

	void Box::OnCreate()
	{
		//ドローコンポーネントの追加と設定
		m_drawComp = AddComponent<PNTStaticDraw>();
		m_drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetTextureResource(L"TEX_BOX");

		//トランスフォームコンポーネント取得と設定
		m_transComp = GetComponent<Transform>();
		m_transComp->SetScale(0.5f, 0.5f, 0.5f);
		m_transComp->SetPosition(Vec3(0.0f, -0.25f, -4.0f));

		//コリジョンつける
		auto ptrColl = AddComponent<CollisionRect>();
		ptrColl->SetFixed(true);

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 125.0f, 640.0f, 480.0f));

	}


	void Box::OnUpdate()
	{
		auto G = GetStage()->GetThis<GameStage>()->GetGameObjectVec();
		//コントローラチェックして入力があればコマンド呼び出し

		MoveXZ();
		BoxMove();
	}

	Vec2 Box::GetInputState() const {
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
			angle *= -moveVec.length();

			//y軸を固定
			angle.y = 0;

			//if (angle.x >= 1.0f)
			//{
			//	angle.z = 0.0f;
			//}
			//else if (angle.z >= 1.0f)
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

		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, 12, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, 12, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, 12, Util::FloatModify::Fixed) + L"\n";
		positionStr += L"direction=" + Util::FloatToWStr(direction, 12, Util::FloatModify::Fixed) + L"\n";
		positionStr += L"deltaZ=" + Util::FloatToWStr(deltaZ, 12, Util::FloatModify::Fixed) + L"\n";
		positionStr += L"ElapssedTime=" + Util::FloatToWStr(elapsedTime, 12, Util::FloatModify::Fixed) + L"\n";

		wstring str = positionStr;


		//文字列コンポーネントの取得
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}


	void Box::MoveXZ() {
		auto angle = GetInputState();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = GetComponent<Transform>()->GetPosition();
		pos += elapsedTime * m_velocity;
		GetComponent<Transform>()->SetPosition(pos);
	}

	void Box::BoxMove()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * 6.0f;
			GetComponent<Transform>()->SetPosition(pos); // 更新後

		}
	}

}
//end basecross
