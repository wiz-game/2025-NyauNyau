/*!
@file BackTitleButton.cpp
@brief ステージスプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void SelectStageSprite::OnCreate()
	{
		// 頂点(Vertex)データを設定
		Col4 color(1, 1, 1, 1);
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

	void SelectStageSprite::OnUpdate()
	{

		if (m_Selected)
		{
			//経過時間を取得
			float elapsedTime = App::GetApp()->GetElapsedTime();

			//時間経過
			m_totalTime += elapsedTime * 3;
			if (m_totalTime >= XM_PI)
			{
				m_totalTime = 0.0f;
			}

			//明滅の変化
			float s = sin(m_totalTime) * 0.75f + 0.25f;
			//ライトの当たり具合
			m_drawComp->SetDiffuse(Col4(1, 1, 1, s));//ｓ：半透明
		}
		else
		{
			m_drawComp->SetDiffuse(Col4(1, 1, 1, 1));
		}

	}

	void SelectStageSprite::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}

	void SelectStageSprite::SetPosition(float x,float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}

	void SelectStageSprite::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}

}
//end basecross
