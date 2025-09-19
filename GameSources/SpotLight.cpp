
/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "SpotLight.h"

namespace basecross {
	SpotLight::SpotLight(const shared_ptr<Stage>& stage,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(stage),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}

	SpotLight::~SpotLight() {}

	void SpotLight::OnCreate()
	{

		// ドローコンポーネントの追加と設定
		//auto drawComp = AddComponent<PNTStaticDraw>();
		//drawComp->SetMeshResource(L"DEFAULT_CUBE"); // キューブ型のメッシュを設定する
		//drawComp->SetOwnShadowActive(true); // 影を受け入れる
		InitDrawComp();

		// トランスフォームコンポーネントの取得と設定
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//コリジョンつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
	}

	void SpotLight::OnUpdate()
	{
	}

	void SpotLight::InitDrawComp()
	{
		Mat4x4 span;
		span.affineTransformation(
			Vec3(1.0f, 1.0f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f,-2.1f, 0.0f)
		);


		m_drawComp = AddComponent<PNTStaticModelDraw>();
		m_drawComp->SetMeshResource(L"MODEL_LAMP");
		m_drawComp->SetEmissive(Col4(1, 1, 1, 1));
		//m_drawComp->SetBlendState(BlendState::Additive);


		m_drawComp->SetMeshToTransformMatrix(span);
	}



}
//end basecross
