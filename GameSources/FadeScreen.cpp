
#include "stdafx.h"
#include "FadeScreen.h"

namespace basecross {

	void FadeScreen::OnCreate()
	{
		// 頂点(Vertex)データを設定
		//全体を覆う透明な黒いスプライト
		Col4 m_color(0, 0, 0, 0);
		m_vertices = {
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
		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, indices); // 頂点データとインデックスデータを設定する
		//m_drawComp->SetTextureResource(L"TEX_TITLESTAGE");
		SetAlphaActive(true);

		// 位置を設定する
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(0, 0, 0); // 画面の中心を原点としたピクセル単位（1280x800）

	}

	void FadeScreen::OnUpdate()
	{
		if (!m_isFading)
		{
			return;
		}

		m_fadeTimer += App::GetApp()->GetElapsedTime();
		float progress = m_fadeTimer / m_fadeDuration;

		if (progress >= 1.0f)
		{
			progress = 1.0f;
			m_isFading = false;

			//フェードが完成したので、登録されていたコールバックを実行
			if (m_onFadeCompleteCallback)
			{
				m_onFadeCompleteCallback();
			}
		}

		//現在のアルファ値を計算
		float currentAlpha = m_startAlpha + (m_endAlpha - m_startAlpha) * progress;
		for (auto& vertex : m_vertices)
		{
			vertex.color.w = currentAlpha;
		}

		m_drawComp->UpdateVertices(m_vertices);
	}

	void FadeScreen::StartFadeOut(float duration, std::function<void()> onComplete) {
		m_fadeDuration = duration;
		m_onFadeCompleteCallback = onComplete;
		m_fadeTimer = 0.0f;
		m_startAlpha = 0.0f;
		m_endAlpha = 1.0f;
		m_isFading = true;
		SetDrawActive(true); // フェード開始時に表示を有効にする
	}

	void FadeScreen::StartFadeIn(float duration, std::function<void()> onComplete) {
		m_fadeDuration = duration;
		m_onFadeCompleteCallback = onComplete;
		m_fadeTimer = 0.0f;
		m_startAlpha = 1.0f;
		m_endAlpha = 0.0f;
		m_isFading = true;
		SetDrawActive(true);
	}
}