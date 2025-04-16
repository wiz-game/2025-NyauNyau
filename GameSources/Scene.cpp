
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			//Col.set(0.0f, 0.0f, 0.0f, 0.0f);//黒
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}

	}

	//AddObject
	void Scene::AddObject(shared_ptr<ObjectInterface> obj)
	{
		m_addObjects.push_back(obj);
	};


	//RemoveObject
	void Scene::RemoveObject(shared_ptr<ObjectInterface> obj) {
		auto it = std::find(m_removeObjects.begin(), m_removeObjects.end(), obj);
		if (it != m_removeObjects.end()) {
			m_removeObjects.erase(it);
		}
	}

}
//end basecross
