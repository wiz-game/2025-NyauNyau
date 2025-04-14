/*!
@file Character.h
@brief スタート
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class startGate : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//構築と破壊
		startGate(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~startGate();
		//初期化
		virtual void OnCreate() override;

	};

}
//end basecross
