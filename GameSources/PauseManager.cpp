/*
@file PauseManager.cpp
@brief ボーズマネージャーの実体
*/

#include "stdafx.h"
#include "Project.h"
#pragma once

namespace basecross {

	//----------------------------------------------------------------------------------------------------------------
	// ポーズマネージャークラス実体
	// ---------------------------------------------------------------------------------------------------------------
	void PauseManager::PauseGame()
	{
		PlayGame(!IsPlaying());

		auto stage = GetStage();
		//ポーズ画面
		Pause = stage->AddGameObject<PauseSprite>();
		Pause->SetTexture(L"TEX_PAUSE");
		Pause->SetPosition(0, 0, 0);
		Pause->SetScale(1.5f, 1.5f, 0);

		//リスタート
		auto restart = stage->AddGameObject<PauseSprite>();
		restart->SetTexture(L"TEX_RESTART");
		restart->SetPosition(0, 20, 0);
		restart->SetScale(0.5f, 0.5f, 0.5f);
		restart->SetSelected(true);
		m_pauseSprites.push_back(restart);//m_pauseSpritesにrestartを入れる

		//タイトルに戻る
		auto title = stage->AddGameObject<PauseSprite>();
		title->SetTexture(L"TEX_BACK");
		title->SetPosition(0, -70.0f, 0);
		title->SetScale(0.5f, 0.5f, 0.5f);
		m_pauseSprites.push_back(title);//m_pauseSpritesにbackを入れる

		//設定
		auto setting = stage->AddGameObject<PauseSprite>();
		setting->SetTexture(L"TEX_SETTING");
		setting->SetPosition(0, -160.0f, 0);
		setting->SetScale(0.47f, 0.47f, 0.47f);
		m_pauseSprites.push_back(setting);//m_pauseSpritesにendを入れる

		//終了
		auto end = stage->AddGameObject<PauseSprite>();
		end->SetTexture(L"TEX_END");
		end->SetPosition(0, -250.0f, 0);
		end->SetScale(0.47f, 0.47f, 0.47f);
		m_pauseSprites.push_back(end);//m_pauseSpritesにendを入れる

		//ネコ矢印
		catPointSprite = stage->AddGameObject<PauseSprite>();
		catPointSprite->SetTexture(L"TEX_POINT");
		catPointSprite->SetPosition(m_selectX + (-200), m_selectY + 20, 0);
		catPointSprite->SetScale(0.2f, 0.2f, 0.2f);

	}

	void PauseManager::OnCreate()
	{
		
	}

	void PauseManager::OnUpdate()
	{
		if (!m_isPlaying)
		{

			//コントローラの取得
			auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			//スタートボタンを押したときにボーズする
			if (CntlVec[0].bConnected)
			{
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START)
				{
					PlayGame(true);
					int m_SpriteNum = GetSpriteNum();

					m_isPlaying = !m_isPlaying;


					//ポーズのスプライトを表示する
					//for (int i = 0; i < 4; i++)
					//{
					//	std::shared_ptr<PauseSprite> sprites = m_pauseSprites[i].lock();
					//	sprites->SetDrawActive(true);
					//}
					//catPointSprite->SetDrawActive(true);
					//Pause->SetDrawActive(true);


						//Aボタンを押したときにゲームステージに移動する

					//CntrolLock = falseの時
					if (!m_CntrolLock)
					{
						//上向き
						if (CntlVec[0].fThumbLY >= 0.8f)
						{
							m_SpriteNum--;
							//ステージ１より上にスティックを動かしたらステージ３に移動
							if (m_SpriteNum < 0)
							{
								m_SpriteNum = 4;
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

						}
						//下向き
						else if (CntlVec[0].fThumbLY <= -0.8f)
						{
							m_SpriteNum++;
							//ステージ３に来たらステージ１に戻る
							if (m_SpriteNum >= 4)
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
			}
			else
			{
				auto stage = GetStage();
				Pause = stage->RemoveGameObject<PauseSprite>(Pause);
				m_pauseSprites = stage->RemoveGameObject<PauseSprite>(m_pauseSprites);
				catPointSprite = stage->RemoveGameObject<PauseSprite>(catPointSprite);

				
				m_isPlaying = false;
				m_CntrolLock = false;
			}


			if (m_isPlaying)
			{
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{
					auto scene = App::GetApp()->GetScene<Scene>();
					switch (m_SpriteNum)
					{
					case 0://リスタート
						PostEvent(0.0f, GetThis<PauseManager>(), scene, L"ToGameStage");
						return;

					case 1://タイトル
						PostEvent(0.0f, GetThis<PauseManager>(), scene, L"ToTitleStage");
						return;

					case 2://設定
						PostEvent(0.0f, GetThis<PauseManager>(), scene, L"ToSettingStage");
						return;

					case 3://終了
						return;

					}
				}
			}
		}
	}

	//選択しているSpriteを点滅させる処理
	void PauseManager::ChangeSelect(int num)
	{
		for (int i = 0; i < 4; i++)
		{
			std::shared_ptr<PauseSprite> srptr = m_pauseSprites[i].lock();
			if (srptr)
			{
				//StageNumがm_pauseSpritesと一致していたら
				if (i == num)
				{

					srptr->SetSelected(true);

				}
				else
				{
					srptr->SetSelected(false);
				}
			}

		}
	}

	//ステージ番号からm_selectを設定する関数
	void PauseManager::SetSelectPosition(int SpriteNum)
	{
		switch (SpriteNum)
		{
		case 0:
			m_selectX = -200.0f;
			m_selectY = 20.0f;
			break;
		case 1:
			m_selectX = -250.0f;
			m_selectY = -70;
			break;
		case 2:
			m_selectX = -200.0f;
			m_selectY = -160.0f;
			break;
		case 3:
			m_selectX = -100.0f;
			m_selectY = -250.0f;
			break;
		default:
			break;
		}
	}


}