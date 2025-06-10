/*!
@file BackTitleButton.cpp
@brief ステージスプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void GameSprite::OnCreate()
	{
		// 頂点(Vertex)データを設定
		Col4 color(0.5f, 0.5f, 0.5f, 0.5f);
		std::vector<VertexPositionColorTexture> vertices = {
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
		m_drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // 頂点データとインデックスデータを設定する
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);
		SetAlphaActive(true);

		// 位置を設定する
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(1, 1, 1);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(0, 0, 0);// 画面の中心を原点としたピクセル単位（1280x800）
	}

	void GameSprite::OnUpdate()
	{

		if (!m_isMoving)
		{
			return;
		}

		if (m_isMoving)
		{
			// 経過時間を取得
			m_totalTime = App::GetApp()->GetElapsedTime();
			Vec3 currentPos = m_ptrTrans->GetPosition();


			// 新しいX座標を計算
			currentPos.x += m_speed * m_moveDirection * m_totalTime;

			// 境界チェック
			// 右の境界を超えた場合
			if (currentPos.x > 600.0f + m_moveRange)
			{
				currentPos.x = 600.0f + m_moveRange; // 境界に位置を補正
				m_moveDirection = -1.0f;      // 方向を左に反転
			}

			// 左の境界を超えた場合
			else if (currentPos.x < 600.0f - m_moveRange)
			{
				currentPos.x = 600.0f - m_moveRange; // 境界に位置を補正
				m_moveDirection = 1.0f;       // 方向を右に反転
			}

			// 計算後の位置を再設定
			m_ptrTrans->SetPosition(currentPos);
		}
	}

	//テクスチャ
	void GameSprite::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}

	//position
	void GameSprite::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}

	//scale
	void GameSprite::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}

}
//end basecross
