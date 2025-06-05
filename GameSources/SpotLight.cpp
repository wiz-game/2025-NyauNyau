
/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void SpotLight::OnCreate()
	{
		SetAlphaActive(true);
		//Col4 color(1.0f, 1.0f, 0.0f, 1.0f);


		//3Dモデルの呼び出し
		InitDrawComp();
	  
		//トランスフォームコンポーネント取得と設定
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(0.25f, 0.25f, 0.25f);
		transComp->SetPosition(10.0f, 15.5f, -30.0f);

		//コリジョンつける
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//タグをつける
		//AddTag(L"SpotLight");
	}

	void SpotLight::OnUpdate()
	{

	}

	void SpotLight::InitDrawComp()
	{
		Mat4x4 span;
		span.affineTransformation(Vec3(0.5f), Vec3(), Vec3(), Vec3(0.0f,-2.1f,0.0f));


		m_drawComp = AddComponent<PNTStaticModelDraw>();
		m_drawComp->SetMeshResource(L"MODEL_LAMP");

		m_drawComp->SetMeshToTransformMatrix(span);
	}



}
//end basecross
