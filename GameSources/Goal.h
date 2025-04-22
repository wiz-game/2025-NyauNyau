/*!
@file Character.h
@brief ƒS[ƒ‹
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class goalGate : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		bool m_gameClear;//shared_ptr‚ÅŠÇ—

	public:
		//\’z‚Æ”j‰ó
		goalGate(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		virtual ~goalGate();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//gameClear‚ÌƒQƒbƒ^[
		bool IsGameClear() const
		{
			return m_gameClear;
		}
	};

}
//end basecross
