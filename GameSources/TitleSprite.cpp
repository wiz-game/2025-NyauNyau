/*!
@file BackgroundTitleSprite.cpp
@brief ゲームクリア スプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void TitleSprite::OnCreate()
	{
		// 頂点(Vertex)データを設定
		Col4 m_color(1, 1, 1, 1);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(-100, +100, 0), m_color, Vec2(0, 0)}, // ①
			{Vec3(+100, +100, 0), m_color, Vec2(1, 0)}, // ②
			{Vec3(-100, -100, 0), m_color, Vec2(0, 1)}, // ③
			{Vec3(+100, -100, 0), m_color, Vec2(1, 1)}, // ④
		};

		// インデックスデータを設定（頂点をつなげる順番・3つの数値を組にして三角形を作る）
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1つ目のポリゴン(三角形)
			2, 1, 3  // 2つ目のポリゴン(三角形)
		};

		// スプライト用のドローコンポーネントを追加する
		m_drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // 頂点データとインデックスデータを設定する
		SetAlphaActive(true);

		// 位置を設定する
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(0, 0, 0); // 画面の中心を原点としたピクセル単位（1280x800）
		m_ptrTrans->SetScale(1, 1, 1);

		m_basePosition = m_ptrTrans->GetPosition();
	}
	
	void TitleSprite::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();
		m_totalTime += delta;

		float amplitude = 10.0f;  // sin波の幅
		float frequency = 2.0f;   // 周期

		// Y方向のオフセットをサイン波で計算
		float y_offset = amplitude * sinf(m_totalTime * frequency + m_phaseOffset);

		// もともとの基準位置に計算したオフセットを加えて、新たな位置に設定
		m_ptrTrans->SetPosition(m_basePosition.x, m_basePosition.y + y_offset, m_basePosition.z);

	}

	void TitleSprite::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}
	void TitleSprite::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}
	void TitleSprite::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}


}
//end basecross
