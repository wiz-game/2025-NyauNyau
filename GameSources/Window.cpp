
/*!
@file Ground.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Window::Window(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		isEnemyHit(false)
	{
	}

	Window::~Window() {}

	void Window::OnCreate()
	{
		//auto drawComp = AddComponent<PNTStaticDraw>();
		//drawComp->SetMeshResource(L"DEFAULT_CUBE"); // キューブ型のメッシュを設定する

		InitDrawComp();

		// トランスフォームコンポーネントの取得と設定
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);


		//コリジョンつける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);


		AddTag(L"Window");

	}

	void Window::OnUpdate()
	{
	}

	void Window::InitDrawComp()
	{
		Mat4x4 span;
		span.affineTransformation(
			Vec3(0.114f, 0.129f, 1.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.5f, 0.0f)
		);

		m_drawComp = AddComponent<PNTStaticModelDraw>();
		m_drawComp->SetMultiMeshResource(L"MODEL_WINDOW");

		m_drawComp->SetMeshToTransformMatrix(span);

	}

}
//end basecross
