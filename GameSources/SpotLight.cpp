
/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void SpotLight::OnCreate()
	{
		//Col4 color(1.0f, 1.0f, 0.0f, 1.0f);


		//ドローコンポーネントの追加と設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		//トランスフォームコンポーネント取得と設定
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(0.25f, 0.25f, 0.25f);
		transComp->SetPosition(3.0f, 0.0f, 0.0f);

		//コリジョンつける
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//タグをつける
		//AddTag(L"SpotLight");
	}

	void SpotLight::OnUpdate()
	{

	}


}
//end basecross
