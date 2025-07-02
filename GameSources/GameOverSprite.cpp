/*!
@file GameOverSprite.cpp
@brief ゲームオーバー スプライト実体
*/

#include "stdafx.h"
#include "GameOverSprite.h"

namespace basecross {

	//初期化
	void GameOverSprite::OnCreate()
	{
		// 頂点(Vertex)データを設定
		Col4 m_color(1, 1, 1, 1);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(-640, +400, 0), m_color, Vec2(0, 0)}, // ①
			{Vec3(+640, +400, 0), m_color, Vec2(1, 0)}, // ②
			{Vec3(-640, -400, 0), m_color, Vec2(0, 1)}, // ③
			{Vec3(+640, -400, 0), m_color, Vec2(1, 1)}, // ④
		};

		// インデックスデータを設定（頂点をつなげる順番・3つの数値を組にして三角形を作る）
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1つ目のポリゴン(三角形)
			2, 1, 3  // 2つ目のポリゴン(三角形)
		};

		// スプライト用のドローコンポーネントを追加する
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // 頂点データとインデックスデータを設定する
		drawComp->SetTextureResource(L"TEX_GAMEOVER");
		SetAlphaActive(true);

		// 位置を設定する
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(0, 50, 0.5f); // 画面の中心を原点としたピクセル単位（1280x800）
	
		m_originalPosition = GetComponent<Transform>()->GetPosition();
	}

	void GameOverSprite::OnUpdate()
	{
		//揺れが始まっていないなら何もしない	
		if (!m_isShaking)
		{
			return;
		}

		// 揺れ時間を減らしていく
		m_shakeDuration -= App::GetApp()->GetElapsedTime();

		// 揺れ時間が終わったら
		if (m_shakeDuration <= 0.0f) {
			m_isShaking = false;
			// 座標を元の位置に戻す
			GetComponent<Transform>()->SetPosition(m_originalPosition);
			return;
		}
		// --- 揺れている間の処理 ---
		// -m_shakePower から +m_shakePower までのランダムな値を生成
		float offsetX = (rand() / (float)RAND_MAX * 2.0f - 1.0f) * m_shakePower;
		float offsetY = (rand() / (float)RAND_MAX * 2.0f - 1.0f) * m_shakePower;

		// 元の位置にランダムなオフセットを加えて座標を設定
		GetComponent<Transform>()->SetPosition(
			m_originalPosition.x + offsetX,
			m_originalPosition.y + offsetY,
			m_originalPosition.z
		);
	}

	//揺れを開始させる関数
	void GameOverSprite::StartShake(float duration, float power) {
		m_isShaking = true;
		m_shakeDuration = duration;//揺れの時間
		m_shakePower = power;//揺れの強さ
		// 念のため、元の位置を再取得しておく
		m_originalPosition = GetComponent<Transform>()->GetPosition();
	}
}
//end basecross
