/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	// 構築と破棄
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position
	) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position), 
		isGameOver(false),
		EnemySpeed(5.58f)
	{
	}

	Enemy::~Enemy() {}


	void Enemy::OnCreate()
	{
		// ドローコンポーネントの追加と設定
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // キューブ型のメッシュを設定する
		drawComp->SetTextureResource(L"TEX_ENEMY");
		SetAlphaActive(true);

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//コリジョン
		auto ptrColl = AddComponent<CollisionObb>();

		AddTag(L"Enemy");

	}


	void Enemy::OnUpdate()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// シーンを取得する
		auto scene = app->GetScene<Scene>();

		// デバッグログを取得する
		wstring log = scene->GetDebugString();
		wstringstream wss(log);
		wss << L"\n\n\n\nGameOver:" << isGameOver;

		scene->SetDebugString(wss.str());

		auto ptrGra = AddComponent<Gravity>();

		// Transform コンポーネントを取得
		auto ptrTransform = GetComponent<Transform>();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		// 現在の位置を取得
		Vec3 currentPosition = ptrTransform->GetPosition();

		// 右方向へ `EnemySpeed` だけ移動
		currentPosition.z += EnemySpeed * elapsedTime;

		// 更新した位置をセット
		ptrTransform->SetPosition(currentPosition);


	}


	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& otherObject)
	{
		if (otherObject->FindTag(L"Player_0")) // "Player" タグを持つオブジェクトと衝突
		{
			isGameOver = true; // ゲームオーバーフラグを設定

			//auto scene = App::GetApp()->GetScene<Scene>();
			//PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");

			////一定時間後にスプライトを削除する（タイトル画面からゲームステージに移るタイミング）
			//PostEvent(5.0f, GetThis<ObjectInterface>(), scene, L"RemoveSprite");

		}

	}
}
//end basecross
