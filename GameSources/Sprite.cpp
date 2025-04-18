/*!
@file Sprite.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void Sprite::OnCreate()
	{
		// 頂点(Vertex)データを設定
		Col4 color(1, 1, 1, 1);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(-640, +400, 0), color, Vec2(0, 0)}, // ①
			{Vec3(+640, +400, 0), color, Vec2(1, 0)}, // ②
			{Vec3(-640, -400, 0), color, Vec2(0, 1)}, // ③
			{Vec3(+640, -400, 0), color, Vec2(1, 1)}, // ④
		};

		// インデックスデータを設定（頂点をつなげる順番・3つの数値を組にして三角形を作る）
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1つ目のポリゴン(三角形)
			2, 1, 3  // 2つ目のポリゴン(三角形)
		};

		// スプライト用のドローコンポーネントを追加する
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // 頂点データとインデックスデータを設定する

		// 位置を設定する
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0, 0, 0); // 画面の中心を原点としたピクセル単位（1280x800）
	}

}
//end basecross
