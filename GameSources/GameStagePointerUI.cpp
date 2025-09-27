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
			{Vec3(-0.6, +0.6, 0), color, Vec2(0, 0)}, // ①
			{Vec3(+0.6, +0.6, 0), color, Vec2(1, 0)}, // ②
			{Vec3(-0.6, -0.6, 0), color, Vec2(0, 1)}, // ③
			{Vec3(+0.6, -0.6, 0), color, Vec2(1, 1)}, // ④
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

		if (m_isAnimation)
		{
			//経過時間を取得
			float elapsedTiem = App::GetApp()->GetElapsedTime();

			//時間経過
			m_totalTime += elapsedTiem * blinkSpeed;
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

			auto drawComp = GetComponent<PCTStaticDraw>();
			//明滅の変化
			float s = sin(m_totalTime) * 0.75f + 0.25f;
			//ライトの当たり具合
			drawComp->SetDiffuse(Col4(1, 1, 1, s));
		}
		else
		{
			return;
		}


		if (m_isAnimating)
		{
			// 前フレームからの経過時間を取得
			float deltaTime = App::GetApp()->GetElapsedTime();

			// 現在のローカルY座標を取得
			float currentY = m_ptrTrans->GetPosition().y;

			// 新しいY座標を計算（現在の位置 ＋ 速度 × 方向 × 時間）
			float newY = currentY + m_speed * m_moveDirection * deltaTime;

			// --- 境界チェック ---
			float upperBound = m_baseOffsetY + m_moveRange; // 上の限界
			float lowerBound = m_baseOffsetY - m_moveRange; // 下の限界

			// 上の限界を超えた場合
			if (newY > upperBound)
			{
				newY = upperBound;      // 境界に位置を補正
				m_moveDirection = -1.0f; // 方向を下向きに反転
			}
			// 下の限界を超えた場合
			else if (newY < lowerBound)
			{
				newY = lowerBound;      // 境界に位置を補正
				m_moveDirection = 1.0f;  // 方向を上向きに反転
			}

			// 計算した新しいローカル座標を設定
			m_ptrTrans->SetPosition(0.0f, newY, 0.0f);
		}
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



	void GameStagePointerUI::SetTargetBox(const shared_ptr<Box>& target, bool isAnimate)
	{
		if (target)
		{
			SetDrawActive(true);
			m_ptrTrans->SetParent(target);//渡されたBoxを追従対象として設定

			m_isAnimating = isAnimate;

					m_ptrTrans->SetPosition(0.0f, m_baseOffsetY + 2.5f, 0.0f);
					m_ptrTrans->SetPosition(0.0f, m_baseOffsetY, 0.0f);
		}
		else
		{
			// ターゲットがnullptrの場合
			SetDrawActive(false);
			m_ptrTrans->SetParent(nullptr);
			m_isAnimating = false;
		}
		m_moveDirection = -1.0f;

	}


	void GameStagePointerUI::SetTargetPlayer(const shared_ptr<Player>& target)
	{
		if (target)
		{
			SetDrawActive(true);
			m_ptrTrans->SetParent(target);//渡されたPlayerを追従対象として設定

			m_isAnimation = true;

			m_ptrTrans->SetPosition(-m_aseOffsetX, m_aseOffsetY, 0.0f);
		}
		else
		{
			// ターゲットがnullptrの場合
			SetDrawActive(false);
			m_ptrTrans->SetParent(nullptr);
			m_isAnimation = false;
		}
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
