/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		//AddObjectの追加
		std::vector<shared_ptr<ObjectInterface>> m_addObjects;

		void AddObject(shared_ptr<ObjectInterface> obj)
		{
			m_addObjects.push_back(obj);
		};


		//RemoveObjectの追加
		std::vector<shared_ptr<ObjectInterface>> m_removeObjects;

		void RemoveObject(shared_ptr<ObjectInterface> obj) {
			auto it = std::find(m_removeObjects.begin(), m_removeObjects.end(), obj);
			if (it != m_removeObjects.end()) {
				m_removeObjects.erase(it);
			}
		}
	};

}

//end basecross
