/*!
@file BackgroundTitleSprite.h
@brief 
*/

#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	class BackgroundTitleSprite : public GameObject;
	//--------------------------------------------------------------------------------------
	class BackgroundTitleSprite : public GameObject
	{

	public:
		// \’z‚Æ”jŠü
		BackgroundTitleSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage)
		{
		}

		virtual ~BackgroundTitleSprite()
		{
		}


		virtual void OnCreate() override; // ‰Šú‰»
		//virtual void OnUpdate() override; // XV
		//virtual void OnDraw() override; // •`‰æ
	};

}
//end basecross
