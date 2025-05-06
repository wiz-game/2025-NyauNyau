/*!
@file TitleStartButton.cpp
@brief スタートボタン スプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void TitleStartButton::OnCreate()
	{
		// 頂点(Vertex)データを設定
		Col4 color(1, 1, 1, 1);
		std::vector<VertexPositionColorTexture> vertices = {
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
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // 頂点データとインデックスデータを設定する
		drawComp->SetTextureResource(L"TEX_TITLESTRATBUTTON");
		SetAlphaActive(true);

		// 位置を設定する
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0, -260, 0); // 画面の中心を原点としたピクセル単位（1280x800）
	}

	void TitleStartButton::OnUpdate()
	{
		//// アルファ値を変更して点滅させる
		//static float time = 0.0f;
		//time += 0.1f; // 時間の進行
		//float alpha = (sin(time) + 1.0f) * 0.5f; // sin波を使ってアルファ値を変化

		//auto drawComp = GetComponent<PCTSpriteDraw>();
		//drawComp->SetAlpha(alpha);

		auto& app = App::GetApp();
		//経過時間を取得
		float elapsedTiem = app->GetElapsedTime();
		//累積時間を保持
		static float accumulatedTime = 0.0f;
		accumulatedTime += elapsedTiem;//経過時間を加算

		//アルファ地の変更を計算
		float alpha = (sin(accumulatedTime) + 1.0f) * 0.5f;

		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->SetAlpha(alpha);
	
	}


}
//end basecross
