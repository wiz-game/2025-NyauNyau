	/*!
@file Character.cpp
@brief ステージセレクト画面の実体
*/

#include "stdafx.h"
#include "Project.h"
#pragma once

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ステージセレクトクラス実体
	//--------------------------------------------------------------------------------------

	//ビューとライトの作成
	void SelectStage::CreateViewLight() {
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

	void SelectStage::OnCreate() {
		try {

			//ビューとライトの作成
			CreateViewLight();

			//テクスチャの読込
			LoadTextures();

			CreateFootprints();

			//スプライトオブジェクトの追加
			//ステージ１
			auto stage1 = AddGameObject<SelectStageSprite>();
			stage1->SetTexture(L"TEX_STAGE1");
			stage1->SetPosition(0, 200.0f, 0);
			stage1->SetSelected(true);
			m_stageSprites.push_back(stage1);//m_stageSpritesにstage1を入れる

			//スタージ２
			auto stage2 = AddGameObject<SelectStageSprite>();
			stage2->SetTexture(L"TEX_STAGE2");
			stage2->SetPosition(0, 0, 0);
			m_stageSprites.push_back(stage2);

			//ステージ３
			auto stage3 = AddGameObject<SelectStageSprite>();
			stage3->SetTexture(L"TEX_STAGE3");
			stage3->SetPosition(0, -200.0f, 0);
			m_stageSprites.push_back(stage3);

			//ネコ矢印
			catPointSprite = AddGameObject<SelectStageSprite>();
			catPointSprite->SetTexture(L"TEX_POINT");
			catPointSprite->SetPosition(-230.0f, m_select + 200.0f, 0);
			catPointSprite->SetScale(0.5f, 0.5f, 0.5f);

			auto scene = App::GetApp()->GetScene<Scene>();
			auto volumeBGM = scene->m_volumeBGM;

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, volumeBGM);


			m_catWalk = AddGameObject<CatWalkSprite>();
			//auto SpriteTrans = catSprite->GetComponent<Transform>();
			//auto SpritePos = SpriteTrans->GetPosition();
			////SpritePos.x = 102.4f;
			//SpriteTrans->SetPosition(SpritePos);
			auto walk = m_catWalk.lock();
			walk->SetDrawActive(false);

			m_loading = AddGameObject<GameSprite>();
			auto loading = m_loading.lock();
			loading->SetTexture(L"TEX_Loading");
			loading->SetPosition(230, -350, 0);
			loading->SetScale(1.0f, 0.5f, 1.0f);
			loading->SetDrawActive(false);
			loading->SetMovementActive(false);

			m_rat = AddGameObject<GameSprite>();
			auto rat = m_rat.lock();
			rat->SetTexture(L"TEX_NEZUMI");
			rat->SetPosition(600.0f, -385.0f, 0);
			rat->SetScale(0.1f, 0.2f, 1.0f);
			rat->SetDrawActive(false);
			rat->SetMovementActive(false);



		}
		catch (...) {
			throw;
		}

	}


	void SelectStage::OnUpdate()
	{
		//シーンの取得
		auto PtrScene = App::GetApp()->GetScene<Scene>();
		int m_StageNum = PtrScene->GetStageNum();



		//コントローラの取得
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CntlVec[0].bConnected)
		{

			//CntrolLock = falseの時
			if (!m_CntrolLock)
			{
				//上向き
				if (CntlVec[0].fThumbLY >= 0.8f)
				{
					m_StageNum--;
					//ステージ１より上にスティックを動かしたらステージ３に移動
					if (m_StageNum < 0)
					{
						m_StageNum = 2;
					}
					m_CntrolLock = true;
					PtrScene->SetStageNum(m_StageNum);
					ChangeSelect(m_StageNum);
					SetSelectYPosition(m_StageNum);
					//ポイントスプライトの座標変更

					if (catPointSprite)
					{
						catPointSprite->SetPosition(-250.0f, m_select, 0);
					}

				}
				//下向き
				else if (CntlVec[0].fThumbLY <= -0.8f)
				{
					m_StageNum++;
					//ステージ３に来たらステージ１に戻る
					if (m_StageNum >= 3)
					{
						m_StageNum = 0;
					}
					m_CntrolLock = true;
					PtrScene->SetStageNum(m_StageNum);
					ChangeSelect(m_StageNum);
					SetSelectYPosition(m_StageNum);
					//ポイントスプライトの座標変更
					if (catPointSprite)
					{
						catPointSprite->SetPosition(-250.0f, m_select, 0);
					}
				}
			//ゲームステージへ
			//Aボタンを押したときにゲームステージに移動する
				if (CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				{
					auto volumeSE = PtrScene->m_volumeSE;
					auto ptrXA = App::GetApp()->GetXAudio2Manager();
					m_SE = ptrXA->Start(L"button_SE", 0, volumeSE);

					StartCatWalkAnimation();
					//return;
					switch (m_StageNum)
					{
					case 0:
						PostEvent(3.0f, GetThis<SelectStage>(), PtrScene, L"ToGameStage");
						break;
					case 1:
						break;
					case 2:
						break;

					default:
						break;
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

		//経過時間を取得
		auto delta = App::GetApp()->GetElapsedTime();

		static float timeElapsed = 0.0f;
		timeElapsed += delta;

		const float frequency = XM_PI / 2.0f;//波の周期

		int index = static_cast<int>(timeElapsed / 0.3f); // 0.3秒ごとに足跡を表示

		if (index < m_footprints.size())
		{
			float waveValue = cos(frequency * index);//sin波の値を計算

			//sin波の値が１または-１に近い場合に表示
			if (waveValue > 0.99f || waveValue < -0.99f)
			{
				auto footprintPtr = m_footprints[index].lock();
				if (footprintPtr)
				{
					if (auto sprite = m_catWalk.lock())
					{
						if (!sprite->IsCatAnimation())
						{
							footprintPtr->SetDrawActive(true); // 足跡を表示
						}
					}
					static float moveDuration = 3.0f;
					static float moveElapsed = 0.0f;

					if (moveElapsed < moveDuration)
					{
						//下から浮き上がってくる演出処理
						moveElapsed += delta;
						//Vec3からfloatへの変換
						Vec3 trans = footprintPtr->GetComponent<Transform>()->GetPosition();
						float startY = trans.y;//Y座標のみ取り出す
						float targetY = startY + 0.3f;//目標の位置

						float setY = startY + (targetY - startY) * (moveElapsed / moveDuration);

						//フェードイン処理
						float alpha = moveElapsed / moveDuration;//透明度の計算（0.0~1.0）
						footprintPtr->SetAlphaActive(alpha);//アルファ値を更新


						footprintPtr->SetPosition(trans.x, setY, 0);
					}
				}
			}
		}
	}

	//選択しているSpriteを点滅させる処理
	void SelectStage::ChangeSelect(int num)
	{
		for (int i = 0; i < 3; i++)
		{
			std::shared_ptr<SelectStageSprite> srptr = m_stageSprites[i].lock();
			if (srptr)
			{
				//StageNumがm_stageSpritesと一致していたら
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
	void SelectStage::SetSelectYPosition(int StageNum)
	{
		switch (StageNum)
		{
		case 0:
			m_select = 200.0f;
			break;
		case 1:
			m_select = 0;
			break;
		case 2:
			m_select = -200.0f;
			break;
		default:
			break;
		}
	}

	//ネコの足跡の処理
	void SelectStage::CreateFootprints()
	{
		//const int footprintCount = 20; // ネコの足跡の数
		//const float startX = -320.0f;  // 初期X座標
		//const float startY = -200.0f;  // 初期Y座標
		//const float endX = 320.0f;
		//const float endY = 200.0f;
		////const float amplitude = 80.0f; // Sin波の振幅（上下の幅）
		////const float frequency = XM_PI / 2.0f; // 波の周期（間隔）

		//Vec3 startPos(startX, startY, 0.0f);//初期位置
		//Vec3 endPos(endX, endY, 0.0f);
		//Vec3 stepPos = endPos - startPos;//ナナメの移動
		//float naname = stepPos.length();
		//float stepLen = naname / footprintCount;
		//Vec3 v = stepPos.normalize();
		//Vec3 z(0, 0, -1);
		//
		//Vec3 cross = v.cross(z);//外積
		//cross = cross.normalize();

		//for (int i = 0; i < footprintCount; i++)
		//{
		//	Vec3 pos(startPos + v * stepLen * i);

		//	if (i % 2 == 0)
		//	{
		//		pos += cross * 200.0f;

		//	}
		//	else
		//	{
		//		pos -= cross * 200.0f;

		//	}

		//	auto footprint = AddGameObject<FootprintSprite>();
		//	footprint->SetTexture(L"TEX_FOOTPRINT");
		//	footprint->SetPosition(pos.x, pos.y, 0);
		//	footprint->SetScale(0.2f, 0.2f, 0.2f);
		//	footprint->SetRotate(0, 0, -(XM_PI / 6));
		//	//footprint->SetDrawActive(false); // 最初は非表示

		//	m_footprints.push_back(footprint);

		const int footprintCount = 20; // ネコの足跡の数
		const float startX = 300.0f;  // 初期X座標
		const float startY = -400.0f;  // 初期Y座標
		const float endX = 630.0f;
		const float endY = -100.0f;
		const float amplitude = 80.0f; // Sin波の振幅（上下の幅）
		const float frequency = XM_PI / 2.0f; // 波の周期（間隔）

		const float stepX = (endX - startX) / footprintCount; // X軸方向の移動量
		const float stepY = (endY - startY) / footprintCount; // Y軸方向の移動量

		for (int i = 0; i < footprintCount; i++)
		{
			auto footprint = AddGameObject<FootprintSprite>();
			footprint->SetTexture(L"TEX_FOOTPRINT");

			float newX = startX + stepX * i + amplitude * cos(frequency * i); //X方向に均等配置
			float newY = startY + stepY * i - 0.3f; //Y方向にSin波を適用 

			footprint->SetPosition(newX, newY, 0);
			footprint->SetScale(0.2f, 0.2f, 0.2f);
			footprint->SetRotate(0, 0, -(XM_PI / 6));
			footprint->SetDrawActive(false); // 最初は非表示

			m_footprints.push_back(footprint);
		}
	}



	void SelectStage::LoadTextures()
	{
		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();

		// メディアフォルダの取得
		auto mediaPath = app->GetDataDirWString();

		// テクスチャフォルダの定義
		auto texPath = mediaPath + L"Textures\\";

		// テクスチャの読込と登録
		app->RegisterTexture(L"TEX_STAGE1", texPath + L"stage1.png");
		app->RegisterTexture(L"TEX_STAGE2", texPath + L"stage2.png");
		app->RegisterTexture(L"TEX_STAGE3", texPath + L"stage3.png");
		app->RegisterTexture(L"TEX_POINT", texPath + L"point.png");
		app->RegisterTexture(L"TEX_POINT2", texPath + L"point2.png");
		app->RegisterTexture(L"TEX_FOOTPRINT", texPath + L"Footprint.png");

		app->RegisterTexture(L"TEX_CatWalk", texPath + L"Cat Walk.png");
		app->RegisterTexture(L"TEX_Loading", texPath + L"Loading.png");
		app->RegisterTexture(L"TEX_NEZUMI", texPath + L"nezumi3.png");


	}

	void SelectStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void SelectStage::StartCatWalkAnimation()
	{
		//スプライトの非表示
		for (int i = 0; i < m_stageSprites.size(); i++)
		{
			auto stagesr = m_stageSprites[i].lock();
			stagesr->SetDrawActive(false);
		}

		catPointSprite->SetDrawActive(false);

		for (auto& sprite : m_footprints)
		{
			if (auto spr = sprite.lock())
			{
				spr->SetDrawActive(false);
			}

		}

		if (auto spr = m_catWalk.lock())
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
	//end basecros