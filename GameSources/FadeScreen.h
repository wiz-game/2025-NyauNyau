#pragma once
#include "stdafx.h"

namespace basecross {
	class FadeScreen : public GameObject {
		
	private:
		shared_ptr < PCTSpriteDraw > m_drawComp;
		std::vector<VertexPositionColorTexture> m_vertices;
		bool m_isFading = false;//現在フェード処理中かどうかのフラグ
		float m_fadeTimer = 0.0f;//フェードが始まってからの経過時間
		float m_fadeDuration = 1.0f;//フェード完了までの総時間
		float m_startAlpha = 0.0f;
		float m_endAlpha = 1.0f;//フェード開始時を終了時のアルファ値（透明度）

		//フェード完了時に呼び出すコールバック関数
		std::function<void()> m_onFadeCompleteCallback;

	public:

		// 構築と破棄
		FadeScreen(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		virtual ~FadeScreen()
		{
		}


		void OnCreate() override;
		void OnUpdate() override;
		
		//フェードアウトの開始
		void StartFadeOut(float duration, std::function<void()> onComplete);

		//フェードインの開始
		void StartFadeIn(float duration, std::function<void()> onComplete);
	};
}