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
		m_soundDistance(20.0f), // 20メートル以内に入ったら鳴く
		m_hasMeowed(false),     // 最初はまだ鳴いていない
		EnemySpeed(9.0f),
		m_CatSound(nullptr)
	{
	}

	Enemy::~Enemy() {}


	void Enemy::OnCreate()
	{
		// ドローコンポーネントの追加と設定
		//auto drawComp = AddComponent<PNTStaticDraw>();
		//drawComp->SetMeshResource(L"DEFAULT_CUBE"); // キューブ型のメッシュを設定する
		//drawComp->SetTextureResource(L"TEX_ENEMY");
		//SetAlphaActive(true);

		InitDrawComp();

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_Scale);
		ptrTransform->SetRotation(m_Rotation);
		ptrTransform->SetPosition(m_Position);

		//コリジョン
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(false);

		AddTag(L"Enemy");

		m_targetPlayer = GetStage()->GetSharedGameObject<GameObject>(L"Player_0");
	}



	void Enemy::OnUpdate()
	{
		//// アプリケーションオブジェクトを取得する
		//auto& app = App::GetApp();

		//// シーンを取得する
		//auto scene = app->GetScene<Scene>();

		//// デバッグログを取得する
		//wstring log = scene->GetDebugString();
		//wstringstream wss(log);
		//wss << L"\n\n\n\nGameOver:" << isGameOver;

		//scene->SetDebugString(wss.str());

		auto ptrGra = AddComponent<Gravity>();

		// Transform コンポーネントを取得
		auto ptrTransform = GetComponent<Transform>();
		float elapsedTime = App::GetApp()->GetElapsedTime();

		// 現在の位置を取得
		Vec3 currentPosition = ptrTransform->GetPosition();

		// 右方向へ `EnemySpeed` だけ移動
		currentPosition.x += EnemySpeed * elapsedTime;

		//auto objects = GetStage()->GetGameObjectVec();
		//for (auto obj : objects)
		//{
		//	auto o = dynamic_pointer_cast<Player>(obj);
		//	o->MovePlayer();
		//}

		// 更新した位置をセット
		ptrTransform->SetPosition(currentPosition);
		m_drawComp->UpdateAnimation(elapsedTime);



		//猫から20.0f内にPlayerが入ったら鳴く
		// weak_ptrからshared_ptrを取得
		if (auto player = m_targetPlayer.lock()) 
		{
			// 自分とプレイヤーのTransformを取得
			auto myPos = GetComponent<Transform>()->GetPosition();
			auto playerPos = player->GetComponent<Transform>()->GetPosition();

			// 2点間の距離を計算
			float distance = (myPos - playerPos).length();

			// 距離がサウンドを鳴らす範囲内に入った場合
			if (distance <= m_soundDistance)
			{
				auto scene = App::GetApp()->GetScene<Scene>();
				auto volumeSE = scene->m_volumeSE;

				// まだ鳴いていなければ、鳴らす
				if (!m_hasMeowed)
				{
					m_hasMeowed = true;

					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					m_CatSound = ptrXA->Start(L"CatVoice", 0, 1.0f);
				}
			}
			// 距離がサウンドを鳴らす範囲外に出た場合
			else
			{
				// フラグをリセットして、次に近づいた時にまた鳴らせるようにする
				m_hasMeowed = false;
			}
		}

	}

	void Enemy::InitDrawComp()
	{
		Mat4x4 span;
		span.affineTransformation
		(
			Vec3(0.1f, 0.1f, 0.01f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -0.55f, 1.0f)
		);

		m_drawComp = AddComponent<PNTBoneModelDraw>();
		m_drawComp->SetMeshResource(L"MODEL_NEKO");
		m_drawComp->AddAnimation(L"ANM_RUN", 0, 24, true);
		m_drawComp->SetMeshToTransformMatrix(span);


	}


	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& otherObject)
	{
		if (otherObject->FindTag(L"Player_0")) // "Player" タグを持つオブジェクトと衝突
		{
			isGameOver = true; // ゲームオーバーフラグを設定
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Stop(m_CatSound);
			m_CatSound = nullptr;
			auto scene = App::GetApp()->GetScene<Scene>();
			auto volumeSE = scene->m_volumeSE;
			ptrXA->Start(L"Fall", 0, volumeSE);

			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToGameOverStage");

		}
		if (otherObject->FindTag(L"ShadowObject")) {
			auto grav = GetComponent<Gravity>();
			grav->StartJump(Vec3(0, 10.0f, 0));
		}
	}
}
//end basecross
