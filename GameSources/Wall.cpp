/*!
@file Wall.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Wall::Wall(const shared_ptr<Stage>& StagePtr,
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
	Wall::~Wall() {}

	//初期化
	void Wall::OnCreate() {
		// ドローコンポーネントの追加と設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SQUARE"); // キューブ型のメッシュを設定する
		//drawComp->SetTextureResource(L"TEX_KABE");
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);
		//コリジョンつける
		/*auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);*/
		drawComp->SetRasterizerState(RasterizerState::Wireframe);
	}

	void Wall::OnUpdate()
	{
	}

	//壁の法線を取得
	Vec3 Wall::GetWallNormal() const
	{
		return GetComponent<Transform>()->GetForward();
	}

	//壁の位置を取得
	Vec3 Wall::GetWallPosition() const
	{
		return GetComponent<Transform>()->GetPosition();

	}
}
//end basecross
