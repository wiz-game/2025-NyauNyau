/*!
@file BackTitleButton.h
@brief ステージスプライトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	
	//--------------------------------------------------------------------------------------
	//	class SelectStageSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class SelectStageSprite : public GameObject
	{
		//トータル時間
		float m_totalTime;
		//選択しているかどうか
		bool m_Selected;
		float blinkSpeed = 3;//点滅速度


		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_ptrTrans;
		

	public:
		// 構築と破棄
		SelectStageSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~SelectStageSprite()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
		void SetTexture(const std::wstring& Key);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);


		//m_Selectedのアクセサ
		int IsSelected() const
		{
			return m_Selected;
		}

		void SetSelected(bool b)
		{
			m_Selected = b;
			m_totalTime = 0.0f;
		}
	};



}
//end basecross
