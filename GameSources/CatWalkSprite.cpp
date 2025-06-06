/*
@file CatWalkSprite.h
@brief 猫のスプライトの実体
*/

#include "stdafx.h"
#include "CatwalkSprite.h"

namespace basecross{

	void CatWalkSprite::OnCreate()
	{
		float texW = 64.0f / 512.0f;
		float texH = 100.0f / 128.0f;
		float left = texW * m_cat;
		float right = left + texW;
		float top = 0.0f;
		float bottom = top + texH;
		m_vertices = {
			{Vec3(0,0,0),m_color,Vec2(left,top)},
			{Vec3(64.0f,0,0),m_color,Vec2(right,top)},
			{Vec3(0,-100.0f,0),m_color,Vec2(left,bottom)},
			{Vec3(64.0f,-100.0f,0),m_color,Vec2(right,bottom)}
		};
		
		// インデックスデータを設定（頂点をつなげる順番・3つの数値を組にして三角形を作る）
		m_indices = {
			0,1,2,// 1つ目のポリゴン(三角形)
			2,1,3 // 2つ目のポリゴン(三角形)
		};
		// スプライト用のドローコンポーネントを追加する

		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);// 頂点データとインデックスデータを設定する
		m_drawComp->SetTextureResource(L"TEX_CatWalk");
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);// テクスチャを繰り返すように貼り付ける設定
		SetAlphaActive(true);

		// 位置を設定する
		m_transComp = GetComponent<Transform>();
		m_transComp->SetPosition(550.0f - 64.0f, -300.0f + 50.0f, 0); // 画面の中心を原点としたピクセル単位（1280x800）
		//m_transComp->SetRotation(0, XM_PI, 0);
		m_transComp->SetScale(1.5f, 1.5f, 1.5f);

	}

	void CatWalkSprite::OnUpdate()
	{
		//アニメーション中でなければ、何もしない
		if (!m_isAnimating)
		{
			return;
		}

		m_animationTime += App::GetApp()->GetElapsedTime();

		//タイマーが一コマの表示時間を超えたら
		if (m_animationTime >= m_frameDuration)
		{
			m_animationTime = 0.0f;
			m_cat++;//次のコマへ
			//最後のコマまで行ったら最初のコマに戻る
			if (m_cat >= m_totalFrames)
			{
				m_cat = 0;
			}

			SetCatNum(m_cat);
		}
	}

	//アニメーションの開始
	void CatWalkSprite::StartAnimation()
	{
		m_isAnimating = true;
		m_animationTime = 0.0f;//タイマーリセット
		m_cat = 0;//最初のコマからスタート
		SetCatNum(m_cat);//最初のコマを表示
	}
	//アニメーションの停止
	void CatWalkSprite::StopAnimation()
	{
		m_isAnimating = false;
	}


	void CatWalkSprite::SetCatNum(int number)
	{
		//エラーチャック（条件が失敗したらプログラムを止める）
		assert(number >= 0 && number < 8);
		//管理している「数値」を更新
		m_cat = number;

		//UV座標における、数字一桁の幅と高さ
		float w = 64.0f / 512.0f;
		float left = w * m_cat;//引数で指定した数字の左側を表す座標

		//新しい数値に合わせて、頂点データを変更する
		m_vertices[0].textureCoordinate.x = left;
		m_vertices[1].textureCoordinate.x = left + w;
		m_vertices[2].textureCoordinate.x = left;
		m_vertices[3].textureCoordinate.x = left + w;
		m_drawComp->UpdateVertices(m_vertices);
	}



}