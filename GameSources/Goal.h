/*!
@file Character.h
@brief ƒS[ƒ‹
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class goalGate : public GameObject
	{
		std::shared_ptr<Transform> m_transComp;
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

	public:
		//\’z‚Æ”j‰ó
		goalGate(const shared_ptr<Stage>& StagePtr,
			 Vec3& Scale,
			 Vec3& Rotation,
			 Vec3& Position
		);

		virtual ~goalGate();
		//‰Šú‰»
		virtual void OnCreate() override;
		virtual void OnUpdate() override;


		void OnCollisionEnter(shared_ptr<GameObject>& collision) override;
	};

}
//end basecross
