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
