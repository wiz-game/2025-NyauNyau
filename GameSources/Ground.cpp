
/*!
@file Ground.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Ground::OnCreate()
	{
		// ドローコンポーネントの追加と設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // キューブ型のメッシュを設定する
		drawComp->SetOwnShadowActive(true); // 影を受け入れる

		// トランスフォームコンポーネントの取得と設定
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(10, 1, 10); // XZ方向に拡大する
		transComp->SetPosition(0, -1.0f, 0);

		//コリジョンつける
		auto ptrColl = AddComponent<CollisionObb>();


	}

	void Ground::OnUpdate()
	{
	}

}
//end basecross
