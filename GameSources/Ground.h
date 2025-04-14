#pragma once
/*!
@file Ground.h
@brief キャラクターなど
*/
#include "stdafx.h"


namespace basecross {

	//ステージに追加可能な地面を表すクラス
	class Ground : public GameObject
	{
	public:
		Ground(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		void OnCreate() override; // 初期設定用のイベントハンドラ
		void OnUpdate() override;
	};
}
//end basecross

