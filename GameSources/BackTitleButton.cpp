/*!
@file BackTitleButton.cpp
@brief スタートボタン スプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void BackTitleButton::OnCreate()
	{
		// 頂点(Vertex)データを設定
		Col4 color(1, 1, 1, 1);
		m_vertices = {
			{Vec3(-200, +100, 0), color, Vec2(0, 0)}, // ①
			{Vec3(+200, +100, 0), color, Vec2(1, 0)}, // ②
			{Vec3(-200, -100, 0), color, Vec2(0, 1)}, // ③
			{Vec3(+200, -100, 0), color, Vec2(1, 1)}, // ④
		};

		// インデックスデータを設定（頂点をつなげる順番・3つの数値を組にして三角形を作る）
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1つ目のポリゴン(三角形)
			2, 1, 3  // 2つ目のポリゴン(三角形)
		};

		// スプライト用のドローコンポーネントを追加する
		auto drawComp = AddComponent<PCTSpriteDraw>(m_vertices, indices); // 頂点データとインデックスデータを設定する
		drawComp->SetTextureResource(L"TEX_TITLESTRATBUTTON");
		drawComp->SetSamplerState(SamplerState::LinearWrap);
		SetAlphaActive(true);

		// 位置を設定する
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(1, 1, 1);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(0, -260.0f, 0);// 画面の中心を原点としたピクセル単位（1280x800）
	}

	void BackTitleButton::OnUpdate()
	{
		//経過時間を取得
		float elapsedTiem = App::GetApp()->GetElapsedTime();

		//時間経過
		m_totalTime += elapsedTiem;
		if (m_totalTime >= XM_PI)
		{
			m_totalTime = 0.0f;
		}

		auto drawComp = GetComponent<PCTSpriteDraw>();
		//明滅の変化
		float s = sin(m_totalTime) * 0.75f + 0.25f;
		//ライトの当たり具合
		drawComp->SetDiffuse(Col4(1, 1, 1, s));
	}


}
//end basecross
