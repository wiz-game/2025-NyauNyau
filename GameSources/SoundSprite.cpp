/*!
@file BackTitleButton.cpp
@brief ステージスプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void SoundSprite::OnCreate()
	{
		m_width = m_ex - m_sx;
		m_height = m_ey - m_sy;

		// 頂点(Vertex)データを設定
		Col4 color(1, 1, 1, 1);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(0, 0, 0), color, Vec2(m_sx/1920.0f, m_sy/1080.0f)}, // ①
			{Vec3(m_width, 0, 0), color, Vec2(m_ex/1920.0f, m_sy/1080.0f)}, // ②
			{Vec3(0, -m_height, 0), color, Vec2(m_sx/1920.0f, m_ey/1080.0f)}, // ③
			{Vec3(m_width, -m_height, 0), color, Vec2(m_ex/1920.0f, m_ey/1080.0f)}, // ④
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

	//テクスチャ
	void SoundSprite::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}

	//position
	void SoundSprite::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}

	//scale
	void SoundSprite::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}

}
//end basecross
