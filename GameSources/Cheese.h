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
		//Vec3 m_Scale;
		//Vec3 m_Rotation;
		//Vec3 m_Position;
		void GetTag(shared_ptr<GameObject>& Player);
		float direction;


	public:
		// 構築と破棄
		Cheese(const shared_ptr<Stage>& stage
			//const Vec3& Scale,
			//const Vec3& Rotation,
			//const Vec3& Position
		);

		virtual ~Cheese();

		virtual void OnCreate() override; //初期化
		virtual void OnUpdate() override; //更新



	};

}
//end basecross
