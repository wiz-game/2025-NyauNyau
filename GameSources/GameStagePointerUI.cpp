/*!
@file BackTitleButton.cpp
@brief ステージスプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void GameStagePointerUI::OnCreate()
	{
		// 頂点(Vertex)データを設定
		Col4 color(1, 1, 1, 1);
		m_vertices = {
			{Vec3(-0.5, +0.5, 0), color, Vec2(0, 0)}, // ①
			{Vec3(+0.5, +0.5, 0), color, Vec2(1, 0)}, // ②
			{Vec3(-0.5, -0.5, 0), color, Vec2(0, 1)}, // ③
			{Vec3(+0.5, -0.5, 0), color, Vec2(1, 1)}, // ④
		};

		// インデックスデータを設定（頂点をつなげる順番・3つの数値を組にして三角形を作る）
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1つ目のポリゴン(三角形)
			2, 1, 3  // 2つ目のポリゴン(三角形)
		};

		// スプライト用のドローコンポーネントを追加する
		m_drawComp = AddComponent<PCTStaticDraw>(); // 頂点データとインデックスデータを設定する
		m_drawComp->CreateOriginalMesh(m_vertices, indices);
		m_drawComp->SetOriginalMeshUse(true);
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);
		m_drawComp->SetBlendState(BlendState::AlphaBlend);//ブレンドステート（色の混ぜ方）を「アルファブレンド」に設定
		//SetAlphaActive(true);

		// 位置を設定する
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(1, 1, 1);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(0, 0, 0);// 画面の中心を原点としたピクセル単位（1280x800）

	}

	void GameStagePointerUI::OnUpdate()
	{
		// 常にカメラの方向を向く（ビルボード処理）
		//auto view = GetStage()->GetView();
		//if (view) {
		//	auto camera = view->GetCamera();
		//	if (camera) {
		//		// カメラのビュー行列の逆行列（＝カメラのワールド行列）を取得
		//		auto cameraWorldMatrix = camera->GetViewMatrix().Inverse();
		//		// ポインターの回転を、カメラの回転と同じにする
		//		m_ptrTrans->SetRotation(cameraWorldMatrix.GetRotation());
		//	}
		//}
	}



	void GameStagePointerUI::SetTargetBox(const shared_ptr<Box>& target)
	{
		SetDrawActive(true);
		m_ptrTrans->SetParent(target);//渡されたBoxを追従対象として設定

		float offset = +2.5f;//どのくらい上に出すか
		m_ptrTrans->SetPosition(0.0f, offset, 0.0f);

	}



	//テクスチャ
	void GameStagePointerUI::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}

	//position
	void GameStagePointerUI::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}

	//scale
	void GameStagePointerUI::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}


	void GameStagePointerUI::SetColor(const Col4& color)
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

	void GameStagePointerUI::SetColor(float r, float g, float b, float a)
	{
		SetColor(Col4(r, g, b, a));
	}

}
//end basecross
