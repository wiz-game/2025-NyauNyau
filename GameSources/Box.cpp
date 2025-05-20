
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

	}

	void Box::OnUpdate()
	{
		float direction = 1.0f; // 移動方向（1.0f:右、-1.0f:左）
		float speed = 1.0f; // 移動速度
		float minX = -2.0f; // 左限界
		float maxX = 2.0f; // 右限界

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = m_transComp->GetPosition();

		pos.z += elapsedTime * speed * direction;

		// 限界を超えたら方向を反転
		if (pos.z > maxX) {
			pos.z = maxX - (pos.z - maxX); // 反転時のオーバーシュートを補正
			direction *= -1.0f; // 左へ移動
		}
		else if (pos.z < minX) {
			pos.z = minX + (minX - pos.z); // 反転時のオーバーシュートを補正
			direction *= 1.0f; // 右へ移動
		}
		m_transComp->SetPosition(pos);
		

	}
}
//end basecross
