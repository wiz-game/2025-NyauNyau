#pragma once
/*!
@file Ground.h
@brief キャラクターなど
*/
#include "stdafx.h"


namespace basecross {

	//ステージに追加可能な地面を表すクラス
	class ShadowFloor : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		ShadowFloor(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~ShadowFloor();


		void OnCreate() override; // 初期設定用のイベントハンドラ
		void OnUpdate() override;
	};
}
//end basecross
