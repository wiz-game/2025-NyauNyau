/*!
@file GameStageUI.h
@brief ステージスプライトなど
*/

#pragma once
#include "stdafx.h"
#include "Box.h"
#include "Player2.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class GameStageUI : public GameObject;
	//--------------------------------------------------------------------------------------
	class GameStageUI : public GameObject
	{
		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;
		std::vector<VertexPositionColorTexture> m_vertices;

		std::weak_ptr<Player> m_target;


		//時間制限のアニメーション用のテクスチャリスト
		vector<shared_ptr<TextureResource>> m_animeTexturesNomal;
		vector<shared_ptr<TextureResource>> m_animeTexturesHurry;
		vector<shared_ptr<TextureResource>> m_animeTexturesDanger;
		//現在再生中のアニメーションテクスチャリストへのポインタ
		vector<shared_ptr<TextureResource>>* m_CurrentAnimeTextures;

		int m_currentFrame;         // 現在表示しているフレームのインデックス
		float m_frameTimer;         // フレームを切り替えるまでの時間を計るタイマー
		float m_timePerFrame;       // 1フレームあたりの表示時間 (例: 0.1秒)
		bool m_isAnimating;         // アニメーションが再生中かどうかのフラグ
		bool m_isLoop;              // アニメーションをループ再生するか

	public:
		// 構築と破棄
		GameStageUI(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_currentFrame(0.0f),
		    m_frameTimer(0.0f),
		    m_timePerFrame(0.0f), // デフォルト値
		    m_isAnimating(false),
		    m_isLoop(false)

		{
		}
		virtual ~GameStageUI()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画

		//void OnUpdateUI();
		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);

		void SetColor(const Col4& color);
		void SetColor(float r, float g, float b, float a);

		// 現在のゲーム時間を引数に取る Update 関数
		void UpdateAnimationByGameTime(float gameTime);
		// アニメーションシーケンスを設定する関数を拡張
		void SetAnimationSequences
		(
			const vector<wstring>& normalKeys,
			const vector<wstring>& hurryKeys,
			const vector<wstring>& dangerKeys
		);

		//アニメーション用の関数
		void SetAnimation(const std::vector<std::wstring>& textureKeys, float timePerFrame, bool loop);
		void PlayAnimation();
		void StopAnimation();

		void SetTargetPlayer(const shared_ptr<Player>& target);
	};
}
//end basecross
