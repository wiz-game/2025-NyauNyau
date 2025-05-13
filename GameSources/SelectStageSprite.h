/*!
@file BackTitleButton.h
@brief ステージスプライトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//ステージ１
	//--------------------------------------------------------------------------------------
	//	class Stage1 : public GameObject;
	//--------------------------------------------------------------------------------------
	class Stage1 : public GameObject
	{
		float m_totalTime;

	public:
		// 構築と破棄
		Stage1(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Stage1()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};


	//ステージ２
	//--------------------------------------------------------------------------------------
	//	class Stage2 : public GameObject;
	//--------------------------------------------------------------------------------------
	class Stage2 : public GameObject
	{
		float m_totalTime;

	public:
		// 構築と破棄
		Stage2(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Stage2()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};



	//ステージ３
	//--------------------------------------------------------------------------------------
	//	class Stage3 : public GameObject;
	//--------------------------------------------------------------------------------------
	class Stage3 : public GameObject
	{
		float m_totalTime;

	public:
		// 構築と破棄
		Stage3(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}
		virtual ~Stage3()
		{
		}

		virtual void OnCreate() override; // 初期化
		virtual void OnUpdate() override; // 更新
		//virtual void OnDraw() override; // 描画
	};


}
//end basecross
