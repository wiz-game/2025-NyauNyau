
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
		//ドローコンポーネントの追加と設定
		//m_drawComp = AddComponent<PNTStaticDraw>();
		//m_drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetTextureResource(L"TEX_BOX");

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

		m_transComp->SetScale(2.5, 2.5f, 2.5f);
		m_transComp->SetPosition(Vec3(10.0f, 16.25f, -20.0f));

		//コリジョンつける
		auto ptrColl = AddComponent<CollisionRect>();
		ptrColl->SetFixed(true);

		auto stage = GetStage();
		auto shadowStrategy = std::make_shared<basecross::BoxShadowStrategy>(stage);
		AddComponent<ShadowComponent>(shadowStrategy);

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 125.0f, 640.0f, 480.0f));
	}

	void Box::OnUpdate()
	{
		auto cntlVec = GetStage()->GetThis<GameStage>()->GetGameObjectVec();
		//コントローラチェックして入力があればコマンド呼び出し

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
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * 6.0f;
			GetComponent<Transform>()->SetPosition(pos); // 更新後
		}

	}

	std::vector<Vec3> Box::GetBoxVertices() const
	{
		/*std::vector<Vec3> boxVertices;

		auto transform = GetComponent<Transform>();
		Vec3 position = transform->GetPosition();
		Vec3 scale = transform->GetScale();

		boxVertices = {
			position + Vec3(-scale.x / 2, -scale.y / 2, -scale.z / 2),
			position + Vec3(scale.x / 2, -scale.y / 2, -scale.z / 2),
			position + Vec3(-scale.x / 2, scale.y / 2, -scale.z / 2),
			position + Vec3(scale.x / 2, scale.y / 2, -scale.z / 2),
			position + Vec3(-scale.x / 2, -scale.y / 2, scale.z / 2),
			position + Vec3(scale.x / 2, -scale.y / 2, scale.z / 2),
			position + Vec3(-scale.x / 2, scale.y / 2, scale.z / 2),
			position + Vec3(scale.x / 2, scale.y / 2, scale.z / 2)
		};

		return boxVertices;*/

		return {
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
			Vec3(1.0f, 1.0f, 1.0f), 
			Vec3(0.0f, 0.0f, 0.0f), 
			Vec3(0.0f, 0.0f, 0.0f), 
			Vec3(0.0f, -0.5f, 0.0f)
		);

		m_drawModelComp = AddComponent<PNTBoneModelDraw>();
		m_drawModelComp->SetMeshResource(L"MODEL_TSUMIKI1");

		m_drawModelComp->SetMeshToTransformMatrix(span);

	}

}
//end basecross
