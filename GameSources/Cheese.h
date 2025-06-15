/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Cheese : public GameObject
	{
		std::shared_ptr<Transform> m_transComp;
		shared_ptr<SoundItem> m_SE;

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		bool isTarget;//追尾状態を管理
		float followDistance;//プレイヤーとの一定距離


	public:
		// 構築と破棄
		Cheese(const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~Cheese();

		virtual void OnCreate() override; //初期化
		virtual void OnUpdate() override; //更新



	};

}
//end basecross
