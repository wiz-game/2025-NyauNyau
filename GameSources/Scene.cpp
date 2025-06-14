
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
			app->RegisterWav(L"button_SE", soundPath + L"button.wav");
			app->RegisterWav(L"Get_SE", soundPath + L"SE_Get.wav");



			//リソース作成
			CreateResourses();

			//クリアする色を設定
			Col4 Col;
			//Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f); //青
			//Col.set(1.0f, 0.0f, 0.0f, 0.0f);//赤
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
		//ステージ２
		if (event->m_MsgStr == L"ToGameStage2") {
			ResetActiveStage<GameStage2>();
		}
		//タイトルステージの設定
		if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		//セレクトステージの設定
		if (event->m_MsgStr == L"ToSelectStage") {
			ResetActiveStage<SelectStage>();
		}
		//ゴールステージの設定
		if (event->m_MsgStr == L"ToGoalStage") {
			ResetActiveStage<goalStage>();
		}
		//セッティングステージの設定
		if (event->m_MsgStr == L"ToSettingStage") {
			ResetActiveStage<SettingStage>();
		}
		//ゲームオーバーステージの設定
		if (event->m_MsgStr == L"ToGameOverStage") {
			ResetActiveStage<GameOverStage>();
		}


	}


}
//end basecross
