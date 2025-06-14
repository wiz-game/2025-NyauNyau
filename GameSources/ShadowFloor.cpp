
/*!
@file Ground.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	ShadowFloor::ShadowFloor(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)
	{
	}
	ShadowFloor::~ShadowFloor() {}

	void ShadowFloor::OnCreate()
	{
		// ドローコンポーネントの追加と設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // キューブ型のメッシュを設定する
		drawComp->SetOwnShadowActive(true); // 影を受け入れる
		drawComp->SetTextureResource(L"TEX_SHELF");

		// トランスフォームコンポーネントの取得と設定
		//auto transComp = GetComponent<Transform>();
		//transComp->SetScale(10, 1, 10); // XZ方向に拡大する
		//transComp->SetPosition(0, -1.0f, 0);
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//コリジョンつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

	}

	void ShadowFloor::OnUpdate()
	{
	}

}
//end basecross
