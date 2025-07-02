/*!
@file Character.cpp
@brief ゲームオーバーステージの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームオーバーステージクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void GameOverStage::CreateViewLight() {
		// カメラの設定
		auto camera = ObjectFactory::Create<Camera>();
		camera->SetEye(Vec3(0.0f, 5.0f, -15.0f));
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// ビューにカメラを設定
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//マルチライトの作成
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //デフォルトのライティングを指定
	}

	void GameOverStage::OnCreate() {
		try {

			//ビューとライトの作成
			CreateViewLight();

			//テクスチャの読込
			LoadTextures();

			m_once = false;

			//スプライトオブジェクト
			//auto Rat = AddGameObject<GameSprite>();
			//Rat->SetTexture(L"TEX_Rat");
			//Rat->SetPosition(0, 150, 0);
			//Rat->SetScale(2.0f, 3.0f, 1.0f);
			//m_sprites.push_back(Rat);

			m_GameOverSprite = AddGameObject<GameOverSprite>();
			m_GameOverSprite.lock()->SetDrawActive(false);


			auto gamestage = AddGameObject<BackTitleButton>();
			gamestage->SetTexture(L"TEX_GameStage");
			gamestage->SetPosition(0, -220, 0);
			gamestage->SetScale(0.75f, 0.5f, 1.0f);
			gamestage->SetSelected(true);
			gamestage->SetDrawActive(false);
			m_SelectSprites.push_back(gamestage);

			auto title = AddGameObject<BackTitleButton>();
			title->SetTexture(L"TEX_BACKTITLE");
			title->SetPosition(0, -320, 0);
			title->SetScale(0.6f, 0.8f, 1.0f);
			title->SetSelected(false);
			title->SetDrawActive(false);
			m_SelectSprites.push_back(title);

			//ロード中のスプライト
			m_catSprite = AddGameObject<CatWalkSprite>();
			auto walk = m_catSprite.lock();
			walk->SetDrawActive(false);

			m_loading = AddGameObject<GameSprite>();
			auto loading = m_loading.lock();
			loading->SetTexture(L"TEX_Loading");
			loading->SetPosition(230, -350, 0);
			loading->SetScale(1.0f, 0.5f, 1.0f);
			loading->SetDrawActive(false);

			m_rat = AddGameObject<GameSprite>();
			auto rat = m_rat.lock();
			rat->SetTexture(L"TEX_NEZUMI");
			rat->SetPosition(610.0f, -385.0f, 0);
			rat->SetScale(0.1f, 0.2f, 1.0f);
			rat->SetDrawActive(false);
			rat->SetMovementActive(false);

			m_TuskSprite = AddGameObject<TuskCatSprite>();
			auto tusk = m_TuskSprite.lock();
			tusk->StartAnimation();

			//ネコ矢印
			catPointSprite = AddGameObject<SelectStageSprite>();
			catPointSprite->SetTexture(L"TEX_POINT");
			catPointSprite->SetPosition(-250.0f, m_selectY - 220.0f, 0);
			catPointSprite->SetScale(0.5f, 0.5f, 0.5f);
			catPointSprite->SetDrawActive(false);

			auto scene = App::GetApp()->GetScene<Scene>();
			auto volumeBGM = scene->m_volumeBGM;
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"GameOverbgm", 0, volumeBGM);

		}
		catch (...) {
			throw;
		}

	}


	void GameOverStage::OnUpdate()
	{
		//0.5秒後にスプライトを表示する
		m_time += App::GetApp()->GetElapsedTime();
		if (m_time > 0.45f)
		{
			SpriteDraw();

			if (m_time > 0.6f)
			{
				m_time = 0.0f;
				//ゲームオーバーのスプライトの揺れ開始
				if (auto spr = m_GameOverSprite.lock())
				{
					// 0.3秒間、強さ8で揺らす
					spr->StartShake(0.3f, 8.0f);
				}
			}
		}

		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto scene = App::GetApp()->GetScene<Scene>();
		auto volumeSE = scene->m_volumeSE;
		auto ptrXA = App::GetApp()->GetXAudio2Manager();

		//スタートボタンを押したときにボーズする
		if (CntlVec[0].bConnected)
		{
			//CntrolLock = falseの時
			if (!m_CntrolLock)
			{
				//上向き
				if (CntlVec[0].fThumbLY >= 0.8f)
				{
					m_SpriteNum--;
					//一番上を上回ったら下に行く
					if (m_SpriteNum < 0)
					{
						m_SpriteNum = 2;
					}
					m_CntrolLock = true;
					SetSpriteNum(m_SpriteNum);
					ChangeSelect(m_SpriteNum);
					SetSelectPosition(m_SpriteNum);
					//ポイントスプライトの座標変更
					if (catPointSprite)
					{
						catPointSprite->SetPosition(-250.0f, m_selectY, 0);
					}

					m_SE = ptrXA->Start(L"SelectButtonSE", 0, volumeSE);

				}
				//下向き
				else if (CntlVec[0].fThumbLY <= -0.8f)
				{
					m_SpriteNum++;
					//一番下を下回ったら上に戻る
					if (m_SpriteNum >= 3)
					{
						m_SpriteNum = 0;
					}
					m_CntrolLock = true;
					SetSpriteNum(m_SpriteNum);
					ChangeSelect(m_SpriteNum);
					SetSelectPosition(m_SpriteNum);
					//ポイントスプライトの座標変更
					if (catPointSprite)
					{
						catPointSprite->SetPosition(-250.0f, m_selectY, 0);
					}
					m_SE = ptrXA->Start(L"SelectButtonSE", 0, volumeSE);
				}
			}
			//動かしていない時
			else
			{
				if (CntlVec[0].fThumbLY == 0.0f)
				{
					m_CntrolLock = false;
				}
			}
		}



		if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
		{
			auto scene = App::GetApp()->GetScene<Scene>();
			auto volumeSE = scene->m_volumeSE;
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_SE = ptrXA->Start(L"button_SE", 0, volumeSE);

			StartCatWalkAnimation();

			switch (m_SpriteNum)
			{
			case 0://ゲームステージに戻る

				PostEvent(0.7f, GetThis<GameOverStage>(), scene, L"ToGameStage");
				return;

			case 1://タイトル
				PostEvent(0.7f, GetThis<GameOverStage>(), scene, L"ToTitleStage");
				return;

			}
		}
	}



	//選択しているSpriteを点滅させる処理
	void GameOverStage::ChangeSelect(int m_SpriteNum)
	{
		for (int i = 0; i < 2; i++)
		{
			//StageNumがm_spritesと一致していたら
			if (i == m_SpriteNum)
			{

				m_SelectSprites[i]->SetSelected(true);

			}
			else
			{
				m_SelectSprites[i]->SetSelected(false);
			}

		}
	}

	//ステージ番号からm_selectを設定する関数
	void GameOverStage::SetSelectPosition(int SpriteNum)
	{
		switch (SpriteNum)
		{
		case 0:
			//m_selectX = -200.0f;
			m_selectY = -220.0f;
			break;
		case 1:
			//m_selectX = -250.0f;
			m_selectY = -320;
			break;
		}
	}


	//コントローラーのAボタンでゲーム画面に移動
	void GameOverStage::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto volumeSE = scene->m_volumeSE;
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		m_SE = ptrXA->Start(L"button_SE", 0, volumeSE);

		if (m_once == false)
		{		
			StartCatWalkAnimation();
			PostEvent(3.0f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");

			m_once = true;
		}
	}

	void GameOverStage::LoadTextures()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// メディアフォルダの取得
		auto mediaPath = app->GetDataDirWString();

		// テクスチャフォルダの定義
		auto texPath = mediaPath + L"Textures\\";

		// テクスチャの読込と登録
		app->RegisterTexture(L"TEX_GAMEOVER", texPath + L"GameOver.png");
		app->RegisterTexture(L"TEX_BACKTITLE", texPath + L"PauseStage title.png");
		app->RegisterTexture(L"TEX_Rat", texPath + L"Rat GameOver.png");
		app->RegisterTexture(L"TEX_GameStage", texPath + L"BackToGameStage.png");
		app->RegisterTexture(L"TEX_TuskCat", texPath + L"Cat_Tusk.png");

	}

	void GameOverStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//スプライトの表示
	void GameOverStage::SpriteDraw()
	{
		if(auto sprite = m_GameOverSprite.lock())
		{
			sprite->SetDrawActive(true);
		}
		catPointSprite->SetDrawActive(true);

		for (auto sprite : m_SelectSprites)
		{
			sprite->SetDrawActive(true);
		}

	}

	void GameOverStage::StartCatWalkAnimation()
	{
		//スプライトの非表示
		if(auto sprite = m_GameOverSprite.lock())
		{
			RemoveGameObject<GameObject>(sprite);
		}
		catPointSprite->SetDrawActive(false);

		for (auto sprite : m_SelectSprites)
		{
			RemoveGameObject<BackTitleButton>(sprite);
		}


		if (auto spr = m_catSprite.lock())
		{
			spr->SetDrawActive(true);
			spr->StartAnimation();
		}
		if (auto spr = m_loading.lock())
		{
			spr->SetDrawActive(true);
		}
		if (auto spr = m_rat.lock())
		{
			spr->SetDrawActive(true);
			spr->SetMovementActive(true);
		}
	}

}
//end basecross
