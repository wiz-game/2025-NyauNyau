/*!
@file GameStageUI.cpp
@brief ステージスプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void GameStageUI::OnCreate()
	{
		// 頂点(Vertex)データを設定
		Col4 color(1, 1, 1, 1);
		m_vertices = {
			{Vec3(-200, +130, 0), color, Vec2(0, 0)}, // ①
			{Vec3(+200, +130, 0), color, Vec2(1, 0)}, // ②
			{Vec3(-200, -130, 0), color, Vec2(0, 1)}, // ③
			{Vec3(+200, -130, 0), color, Vec2(1, 1)}, // ④
		};

		// インデックスデータを設定（頂点をつなげる順番・3つの数値を組にして三角形を作る）
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1つ目のポリゴン(三角形)
			2, 1, 3  // 2つ目のポリゴン(三角形)
		};

		// スプライト用のドローコンポーネントを追加する
		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, indices); // 頂点データとインデックスデータを設定する
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);
		m_drawComp->SetBlendState(BlendState::AlphaBlend);//ブレンドステート（色の混ぜ方）を「アルファブレンド」に設定
		SetAlphaActive(true);

		// 位置を設定する
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(1, 1, 1);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(0, 0, 0);// 画面の中心を原点としたピクセル単位（1280x800）

	}

	void GameStageUI::OnUpdate()
	{
		if (!m_isAnimating || m_CurrentAnimeTextures.empty()) 
		{
			return; // アニメーションが再生中でないか、テクスチャがなければ何もしない
		
		}
	}

	//テクスチャ
	void GameStageUI::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}

	//position
	void GameStageUI::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}

	//scale
	void GameStageUI::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}


	void GameStageUI::SetColor(const Col4& color)
	{
		//保持している全頂点の色情報を更新
		for (auto& vertex : m_vertices)
		{
			vertex.color = color;
		}
		if (m_drawComp)
		{
			m_drawComp->UpdateVertices(m_vertices);
		}
	}

	void GameStageUI::SetColor(float r, float g, float b, float a)
	{
		SetColor(Col4(r, g, b, a));
	}

	//ゲーム時間に応じて、再生するアニメーションシーケンスを決定
	void GameStageUI::UpdateAnimationByGameTime(float gameTime)
	{
		//ゲーム時間に応じて、再生するアニメーションシーケンスを決定
		if (gameTime > 25.0f)
		{
			m_CurrentAnimeTextures = &m_animeTexturesDanger;
		}
		else if (gameTime > 15.0f)
		{
			m_CurrentAnimeTextures = &m_animeTexturesHurry;
		}
		else
		{
			m_CurrentAnimeTextures = &m_animeTexturesNomal;
		}

		//選択されたシーケンスでアニメーションを再生(通常のOnUpdateのロジック)
		if (!m_CurrentAnimeTextures || m_CurrentAnimeTextures->empty())
		{
			return;
		}

		m_frameTimer += App::GetApp()->GetElapsedTime();
		if (m_frameTimer >= m_timePerFrame)
		{
			m_frameTimer -= m_timePerFrame;
			m_currentFrame++;
			if (m_currentFrame >= m_CurrentAnimeTextures->size())
			{
				m_currentFrame = 0; //常にループする
			}

			auto drawComp = GetComponent<SpriteBaseDraw>();
			if (drawComp)
			{
				drawComp->SetTextureResource((*m_CurrentAnimeTextures)[m_currentFrame]);
			}
		}
	}

}
//end basecross
