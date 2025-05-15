
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
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetTextureResource(L"TEX_BOX");

		//トランスフォームコンポーネント取得と設定
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(0.5f, 0.5f, 0.5f);
		transComp->SetPosition(Vec3(3.0f, 0.0f, -4.0f));

		//コリジョンつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

	}

	void Box::OnUpdate()
	{

	}
}
//end basecross
