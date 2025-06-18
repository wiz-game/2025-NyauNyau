/*!
@file BackTitleButton.cpp
@brief ステージスプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//初期化
	void GameStageUI::OnCreate()
	{
		// 頂点(Vertex)データを設定
		Col4 color(1, 1, 1, 1);
		m_vertices = {
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
		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, indices); // 頂点データとインデックスデータを設定する
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);
		m_drawComp->SetBlendState(BlendState::AlphaBlend);//ブレンドステート（色の混ぜ方）を「アルファブレンド」に設定
		SetAlphaActive(true);

		// 位置を設定する
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(1, 1, 1);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(0, 0, 0);// 画面の中心を原点としたピクセル単位（1280x800）

		////文字列をつける
		//auto ptrString = AddComponent<StringSprite>();
		//ptrString->SetText(L"");
		//ptrString->SetTextRect(Rect2D<float>(50.0f, 100.0f, 640.0f, 480.0f));
	}

	void GameStageUI::OnUpdate()
	{

		//// デバッグ文字列を組み立てるための wstring
		//wstring debugStr = L"--- GameStageUI Debug ---\n";

		//// 1. ターゲットのBoxを確認
		//auto targetBox = m_targetBox.lock();
		//if (!targetBox) {
		//	debugStr += L"Target: NULL\n";
		//	debugStr += L"Status: Hiding (No Target)\n";
		//	SetDrawActive(false);

		//	// 最後にデバッグ文字列をセット
		//	auto ptrString = GetComponent<StringSprite>();
		//	ptrString->SetText(debugStr);
		//	return;
		//}

		//// ターゲットが見つかった場合
		//debugStr += L"Target: FOUND!\n";
		////debugStr += L"Target Name: " + targetBox->GetTag() + L"\n"; // Boxのタグ名を表示

		//// 2. ViewとCameraを確認
		//auto view = GetStage()->GetView();
		//auto singleView = view ? std::dynamic_pointer_cast<SingleView>(view) : nullptr;
		//auto camera = singleView ? singleView->GetTargetCamera() : nullptr;

		//if (!camera) {
		//	debugStr += L"Camera: NULL\n";
		//	debugStr += L"Status: Hiding (No Camera)\n";
		//	SetDrawActive(false);

		//	auto ptrString = GetComponent<StringSprite>();
		//	ptrString->SetText(debugStr);
		//	return;
		//}

		//// カメラが見つかった場合
		//debugStr += L"Camera: FOUND!\n";

		//// 3. 座標変換を実行
		//Vec3 boxPosition = targetBox->GetComponent<Transform>()->GetPosition();
		//Vec3 worldOffset(0.0f, 2.0f, 0.0f);
		//Vec3 targetWorldPos = boxPosition + worldOffset;

		//const auto& viewMatrix = camera->GetViewMatrix();
		//const auto& projMatrix = camera->GetProjMatrix();
		//const auto& viewport = singleView->GetTargetViewport();
		//auto wvpMatrix = viewMatrix * projMatrix;
		//Vec4 worldPos4(targetWorldPos.x, targetWorldPos.y, targetWorldPos.z, 1.0f);
		//Vec4 clipPos = worldPos4 * wvpMatrix;

		//debugStr += L"WorldPos: " + Util::FloatToWStr(targetWorldPos.x, 2) + L", "
		//	+ Util::FloatToWStr(targetWorldPos.y, 2) + L", "
		//	+ Util::FloatToWStr(targetWorldPos.z, 2) + L"\n";

		//debugStr += L"ClipPos: " + Util::FloatToWStr(clipPos.x, 2) + L", "
		//	+ Util::FloatToWStr(clipPos.y, 2) + L", "
		//	+ Util::FloatToWStr(clipPos.z, 2) + L", "
		//	+ Util::FloatToWStr(clipPos.w, 2) + L"\n";

		//// 4. 画面外判定
		//if (clipPos.w <= 0.0f || abs(clipPos.x) > clipPos.w || abs(clipPos.y) > clipPos.w) {
		//	debugStr += L"Status: Hiding (Outside View)\n";
		//	SetDrawActive(false);
		//	auto ptrString = GetComponent<StringSprite>();
		//	ptrString->SetText(debugStr);
		//	return;
		//}

		//// 5. スクリーン座標計算
		//Vec3 ndcPos(clipPos.x / clipPos.w, clipPos.y / clipPos.w, clipPos.z / clipPos.w);
		//Vec2 screenPos;
		//screenPos.x = (ndcPos.x + 1.0f) * 0.5f * viewport.Width + viewport.TopLeftX;
		//screenPos.y = (1.0f - ndcPos.y) * 0.5f * viewport.Height + viewport.TopLeftY;

		//debugStr += L"ScreenPos: " + Util::FloatToWStr(screenPos.x, 2) + L", "
		//	+ Util::FloatToWStr(screenPos.y, 2) + L"\n";
		//debugStr += L"Status: Drawing!\n";

		//// 6. UIの位置を更新して表示
		//m_ptrTrans->SetPosition(screenPos.x, screenPos.y, 0.0f);
		//SetDrawActive(true);

		//// 最後にデバッグ文字列をセット
		//auto ptrString = GetComponent<StringSprite>();
		//ptrString->SetText(debugStr);

		//追尾フラグがOFFなら何もしない
		if (!m_isTracking)
		{
			return;
		}

		auto targetBox = m_targetBox.lock();
		if (!targetBox)
		{
			SetDrawActive(false);
			return;
		}

		//ビューまたはカメラが取得できなければ終了
		auto view = GetStage()->GetView();
		auto singleView = std::dynamic_pointer_cast<SingleView>(view);
		auto camera = singleView ? singleView->GetTargetCamera() : nullptr;
		if (!camera)
		{
			SetDrawActive(false);
			return;
		}

		// --- 座標変換 ---
		Vec3 boxPosition = targetBox->GetComponent<Transform>()->GetPosition();
		Vec3 targetWorldPos = boxPosition + m_worldOffset;

		//ワールド座標(Vec3)を、計算のために同次座標(Vec4)に変換する
		Vec4 worldPos4(targetWorldPos.x, targetWorldPos.y, targetWorldPos.z, 1.0f);

		//NDCを、ピクセル単位のスクリーン座標に変換する
		Vec2 screenPos;
		//const auto& viewport = singleView->GetTargetViewport();

		if (ProjectWorldToScreen(targetWorldPos, camera, singleView->GetTargetViewport(), screenPos))
		{
			m_ptrTrans->SetPosition(screenPos.x, screenPos.y - 50.0f, 0.0f);
			SetDrawActive(true);
		}
		else
		{
			SetDrawActive(false);
		}
	}



	void GameStageUI::SetTargetBox(const shared_ptr<Box>& target)
	{
		m_targetBox = target;//渡されたBoxを追従対象として設定
		//ターゲットが設定されたら追尾開始
		m_isTracking = (target != nullptr);
	}


	bool GameStageUI::ProjectWorldToScreen(const Vec3& worldPos,
		const shared_ptr<Camera>& camera,
		const basecross::Viewport& viewport,
		Vec2& outScreenPos) // 結果を引数で受け取る
	{
		//変換に必要な行列とビューポートを取得
		const auto& viewMatrix = camera->GetViewMatrix();
		const auto& projMatrix = camera->GetProjMatrix();
		// ワールド→ビュー→プロジェクションの変換行列を一つにまとめる
		auto wvpMatrix = viewMatrix * projMatrix;

		//行列を適用して、ワールド座標をクリップ座標に変換する
		Vec4 clipPos = Vec4(worldPos, 1.0f) * wvpMatrix;


		//カメラの視錐台の外にあるオブジェクトは描画しない
		// (wが0以下はカメラの後ろ、x,yがwを超えると画面外)
		if (clipPos.w <= 0.0f ||
			abs(clipPos.x) > clipPos.w ||
			abs(clipPos.y) > clipPos.w)
		{
			return false;
		}

		//透視除算（wで割る）を行い、正規化デバイス座標(NDC)を求める
//    これで座標が-1.0～+1.0の範囲に収まる。
		Vec3 ndcPos(clipPos.x / clipPos.w, clipPos.y / clipPos.w, clipPos.z / clipPos.w);

		outScreenPos.x = (ndcPos.x + 1.0f) * 0.5f * viewport.Width + viewport.TopLeftX;
		outScreenPos.y = (1.0f - ndcPos.y) * 0.5f * viewport.Height + viewport.TopLeftY; // Y軸は上下が逆							m_ptrTrans->SetPosition(screenPos.x, screenPos.y + 50, 0.0f);

		return true;
	}


	//テクスチャ
	void GameStageUI::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}

	//position
	void GameStageUI::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}

	//scale
	void GameStageUI::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}


	void GameStageUI::SetColor(const Col4& color)
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

	void GameStageUI::SetColor(float r, float g, float b, float a)
	{
		SetColor(Col4(r, g, b, a));
	}

}
//end basecross
