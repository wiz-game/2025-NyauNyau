
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
<<<<<<< HEAD
		transComp->SetScale(0.5f, 0.5f, 0.5f);
		transComp->SetPosition(Vec3(-4.75f, 0.0f, -4.0f));
=======
		transComp->SetScale(1.0f, 1.0f, 1.0f);
		transComp->SetPosition(Vec3(-1.0f, 0.125f, 0));
>>>>>>> Takumu_Honda-

		//コリジョンつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

	}

	void Box::OnUpdate()
	{

	}
}
//end basecross
