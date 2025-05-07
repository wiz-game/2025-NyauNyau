
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
	void Scene::CreateResourses()
	{
	}
	void Scene::OnCreate(){
		try {


			// アプリケーションオブジェクトを取得する
			auto& app = App::GetApp(); // アプリケーションオブジェクト(シングルトン)のインスタンスを取得する

			// メディアフォルダの取得
			auto mediaPath = app->GetDataDirWString();

			// サウンドフォルダの定義
			auto soundPath = mediaPath + L"Sounds\\";


			app->RegisterWav(L"Titlebgm", soundPath + L"audiostock_864577.wav");
			//app->RegisterWav(L"Gamebgm", soundPath + L"audiostock_1224243.wav");
			app->RegisterWav(L"Gamebgm", soundPath + L"audiostock_1495090.wav");
			app->RegisterWav(L"GameOverbgm", soundPath + L"audiostock_1042193.wav");
			app->RegisterWav(L"GameClearbgm", soundPath + L"audiostock_842617.wav");




			//リソース作成
			CreateResourses();

			//クリアする色を設定
			Col4 Col;
			//Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			Col.set(0.0f, 0.0f, 0.0f, 0.0f);//黒
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
		//タイトルステージの設定
		if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		//ゴールステージの設定
		if (event->m_MsgStr == L"ToGoalStage") {
			ResetActiveStage<goalStage>();
		}

	}


}
//end basecross
