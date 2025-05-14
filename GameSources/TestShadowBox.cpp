#include "stdafx.h"
#include "Project.h"


namespace basecross
{
	//構築と破棄
	TestShadowBox::TestShadowBox(const shared_ptr<Stage>& StagePtr,
		 Vec3& Scale,
		 Vec3& Rotation,
		 Vec3& Position

	):

		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position)

	{}


	void TestShadowBox::OnCreate()
	{
		// ドローコンポーネントの追加と設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // キューブ型のメッシュを設定する
		//drawComp->SetOwnShadowActive(true); // 影を受け入れる
		//drawComp->SetTextureResource(L"TEX_YUKA");

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//コリジョンつける
		auto ptrColl = AddComponent<CollisionRect>();
		ptrColl->SetFixed(true);

		//各パフォーマンスを得る
		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);


	}

	void TestShadowBox::OnUpdate()
	{
	}



}