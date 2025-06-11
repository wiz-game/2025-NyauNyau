#include "stdafx.h"
#include "Project.h"


namespace basecross
{
	void ShadowBall::OnCreate()
	{
		//ドローコンポーネントの追加と設定
		m_drawComp = AddComponent<PNTStaticDraw>();
		m_drawComp->SetMeshResource(L"DEFAULT_CUBE");

		//トランスフォームコンポーネント取得と設定
		m_transComp = GetComponent<Transform>();
		m_transComp->SetScale(m_Scale);
		m_transComp->SetRotation(m_Rotation);
		m_transComp->SetPosition(m_Position);


		//コリジョンつける
		auto ptrColl = AddComponent<CollisionSphere>();
		auto ptrGra = AddComponent<Gravity>();

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 250.0f, 640.0f, 480.0f));


	}

	void ShadowBall::OnUpdate()
	{
		DrawStrings();

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = m_transComp->GetPosition();

		auto Stage = GetStage();
		auto Ball = Stage->GetSharedGameObject<ShadowBall>(L"Ball_0");
		auto Ball2 = Stage->GetSharedGameObject<ShadowBall>(L"Ball_1");

		if (Ball)
		{
			pos.x -= m_Speed * elapsedTime;
		}
		else if (Ball2)
		{
			pos.x += m_Speed * elapsedTime;
		}

		GetComponent<Transform>()->SetPosition(pos); // 更新後


	}

	void ShadowBall::DrawStrings()
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
