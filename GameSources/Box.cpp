
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
		m_transComp->SetPosition(Vec3(0.0f, -0.25f, 0.0f));

		//コリジョンつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 125.0f, 640.0f, 480.0f));

	}

	void Box::OnUpdate()
	{
		float direction = 1.0f; // 移動方向（1.0f:右、-1.0f:左）
		float speed = 1.0f; // 移動速度
		float minX = -3.0f; // 左限界
		float maxX = 3.0f; // 右限界

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = m_transComp->GetPosition();

		float deltaZ = elapsedTime * speed * direction;

		// **境界チェックの処理を修正**
		if (pos.z + deltaZ >= maxX) {
			direction *= -1.0f;
			pos.z = maxX - (deltaZ); // **超えた分だけを反映して折り返し**
		}
		else if (pos.z + deltaZ <= minX) {
			direction *= -1.0f;
			pos.z = minX + (deltaZ); // **超えた分だけを反映して折り返し**
		}
		else {
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
}
//end basecross
