
/*!
@file Ground.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	BookShelf::BookShelf(const shared_ptr<Stage>& StagePtr,
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

	BookShelf::~BookShelf() {}

	void BookShelf::OnCreate()
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

	void BookShelf::OnUpdate()
	{
	}

	void BookShelf::InitDrawComp()
	{
		Mat4x4 span;
		span.affineTransformation(
			Vec3(0.0494f, 0.0494f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.35f, 1.5f)
		);

		m_drawComp = AddComponent<PNTStaticModelDraw>();
		m_drawComp->SetMeshResource(L"MODEL_BOOKSHELF");

		m_drawComp->SetMeshToTransformMatrix(span);

	}



}
//end basecross
