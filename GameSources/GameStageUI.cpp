/*!
@file BackTitleButton.cpp
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
		if (m_isAnimation)
		{
			//経過時間を取得
			float elapsedTiem = App::GetApp()->GetElapsedTime();

			//時間経過
			m_totalTime += elapsedTiem * blinkSpeed;
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			auto drawComp = GetComponent<PCTSpriteDraw>();
			//明滅の変化
			float s = sin(m_totalTime) * 0.75f + 0.25f;
			//ライトの当たり具合
			drawComp->SetDiffuse(Col4(1, 1, 1, s));
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

	void GameStageUI::SetTargetPlayer(const shared_ptr<Player>& target)
	{
		if (target)
		{
			SetDrawActive(true);
			m_ptrTrans->SetParent(target);//渡されたPlayerを追従対象として設定

			m_isAnimation = true;

			m_ptrTrans->SetPosition(m_baseOffsetX, m_baseOffsetY, 0.0f);
		}
		else
		{
			// ターゲットがnullptrの場合
			SetDrawActive(false);
			m_ptrTrans->SetParent(nullptr);
			m_isAnimation = false;
		}
	}

//end basecross
