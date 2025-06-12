
/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

#include "ShadowObject.h"
#include "RaycastLine.h"
namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {

		m_mainView = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrmainCamera = ObjectFactory::Create<MainCamera>();
		ptrmainCamera->SetEye(Vec3(12.0f, 0.0f, 10.0f));
		ptrmainCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		m_mainView->SetCamera(ptrmainCamera);


		m_phase1View = ObjectFactory::Create<SingleView>(GetThis<Stage>());
		auto ptrphase1Camera = ObjectFactory::Create<Phase1Camera>();
		ptrphase1Camera->SetEye(Vec3(10.0f, 30.0f, -60.0f));
		ptrphase1Camera->SetAt(Vec3(10.0f, 20.0f, 0.0f));
		m_phase1View->SetCamera(ptrphase1Camera);

		SetView(m_phase1View);





		//�}���`���C�g�̍쐬
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //�f�t�H���g�̃��C�e�B���O���w��



		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateWall()
	{
		vector<vector<Vec3>> vec = {
			{
				Vec3(200.0f, 200.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 4.0f, 0.0f)
			},
			//{
			//	Vec3(100.0f, 50.0f, 1.0f),
			//	Vec3(0.0f, -XM_PI / 2, 0.0f),
			//	Vec3(-5.0f, 4.0f, 0.0f)
			//},

		};

		int index = 0; // ���j�[�N���p�̃C���f�b�N�X
		vector<shared_ptr<Wall>> walls; // �������� `Wall` ���Ǘ����郊�X�g

		for (auto& v : vec) {
			auto ptrWall = AddGameObject<Wall>(v[0], v[1], v[2]);

			// ���j�[�N���𐶐�
			wstring uniqueTag = L"Wall_" + to_wstring(index);

			ptrWall->AddTag(uniqueTag);  // ���j�[�N�ȃ^�O��K�p
			walls.push_back(ptrWall);    // `Wall` �����X�g�ɕۑ�

			index++; // ���̃I�u�W�F�N�g�̂��߂ɃC���f�b�N�X�𑝉�
		}

		// ���ׂĂ� `Wall` �����L�Q�[���I�u�W�F�N�g�Ƃ��ēo�^
		for (size_t i = 0; i < walls.size(); ++i) {
			wstring uniqueName = L"Wall_" + to_wstring(i);  // ���j�[�N���𐶐�
			SetSharedGameObject(uniqueName, walls[i]);      // ���j�[�N���ŋ��L�o�^
		}
	}

	void GameStage::CreateGround()
	{
		vector<vector<Vec3>> vec = {
		{
			Vec3(200.0f, 10.0f, 200.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -10.5f, 0.0f)
		},
			//{
			//	Vec3(20.0f, 1.0f, 8.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-8.0f, -1.0f, 6.0f)
			//},
			//{
			/*	Vec3(8.0f, 1.0f, 20.0f),
				Vec3(0.0f,  0.0f, 0.0f),
				Vec3(0.0f, -1.0f, 6.0f)*/

				//}

		};

		int index = 0; // ���j�[�N���p�̃C���f�b�N�X
		vector<shared_ptr<Ground>> grounds; // �������� `Ground` ���Ǘ����郊�X�g

		for (auto& v : vec)
		{
			auto ptrGround = AddGameObject<Ground>(v[0], v[1], v[2]);

			// ���j�[�N���𐶐�
			wstring uniqueTag = L"Ground_" + to_wstring(index);

			ptrGround->AddTag(uniqueTag);  // ���j�[�N�ȃ^�O��K�p
			grounds.push_back(ptrGround);    // `Ground` �����X�g�ɕۑ�

			index++; // ���̃I�u�W�F�N�g�̂��߂ɃC���f�b�N�X�𑝉�
		}

		// ���ׂĂ� `Ground` �����L�Q�[���I�u�W�F�N�g�Ƃ��ēo�^
		for (size_t i = 0; i < grounds.size(); ++i) {
			wstring uniqueName = L"Ground_" + to_wstring(i);  // ���j�[�N���𐶐�
			SetSharedGameObject(uniqueName, grounds[i]);      // ���j�[�N���ŋ��L�o�^
		}

	}

	void GameStage::CreateShadowFloor()
	{
		vector<vector<Vec3>> vec = {
		{
			Vec3(20.0f, 20.0f, 1.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 4.0f, 0.0f)
		},
		};

		int index = 0; // ���j�[�N���p�̃C���f�b�N�X
		vector<shared_ptr<ShadowFloor>> grounds; // �������� `Ground` ���Ǘ����郊�X�g

		for (auto& v : vec) {
			auto ptrGround = AddGameObject<ShadowFloor>(v[0], v[1], v[2]);

			// ���j�[�N���𐶐�
			wstring uniqueTag = L"Ground_1" + to_wstring(index);

			ptrGround->AddTag(uniqueTag);  // ���j�[�N�ȃ^�O��K�p
			grounds.push_back(ptrGround);    // `Ground` �����X�g�ɕۑ�

			index++; // ���̃I�u�W�F�N�g�̂��߂ɃC���f�b�N�X�𑝉�
		}

		// ���ׂĂ� `Ground` �����L�Q�[���I�u�W�F�N�g�Ƃ��ēo�^
		for (size_t i = 0; i < grounds.size(); ++i) {
			wstring uniqueName = L"Ground_1" + to_wstring(i);  // ���j�[�N���𐶐�
			SetSharedGameObject(uniqueName, grounds[i]);      // ���j�[�N���ŋ��L�o�^
		}

	}

	void GameStage::CreateTable()
	{
		vector<vector<Vec3>> vec = {
		{
		Vec3(30.0f, 30.0f, 30.0f),  // 10,1,10
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(10.0f, 0.0f, -30.0f)
		},
		};

	}


	//�X�^�[�g
	void GameStage::CreatestartGate()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.0f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-40.0f,0.005f,-0.5f)
		}
		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
			AddGameObject<startGate>(v[0], v[1], v[2]);
		}
	}

	//�v���C���[
	void GameStage::CreatePlayer()
	{
		vector<vector<Vec3>> vec =
		{
			{
				Vec3(1.25f, 1.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-25.0f, 22.5f, -0.5f)
				//Vec3(-25.0f, 0.5f, -0.2f)
			},

		};

		int index = 0; // ���j�[�N���p�̃C���f�b�N�X
		vector<shared_ptr<Player>> players; // �������� `Player` ���Ǘ����郊�X�g

		for (auto& v : vec)
		{
			auto ptrPlayer = AddGameObject<Player>(v[0], v[1], v[2]);
			auto ptrmainCamera = dynamic_pointer_cast<MainCamera>(m_mainView->GetCamera());
			ptrmainCamera->SetTargetObject(ptrPlayer);

			// ���j�[�N���𐶐�
			wstring uniqueTag = L"Player_" + to_wstring(index);

			ptrPlayer->AddTag(uniqueTag);  // ���j�[�N�ȃ^�O��K�p
			players.push_back(ptrPlayer);    // `Player` �����X�g�ɕۑ�
			index++; // ���̃I�u�W�F�N�g�̂��߂ɃC���f�b�N�X�𑝉�		

		}

		players[0]->SetPlayerMove(false);
		//players[1]->SetPlayerMove(true);


		// ���ׂĂ� `Player` �����L�Q�[���I�u�W�F�N�g�Ƃ��ēo�^
		for (size_t i = 0; i < players.size(); i++)
		{
			wstring uniqueName = L"Player_" + to_wstring(i);  // ���j�[�N���𐶐�
			SetSharedGameObject(uniqueName, players[i]);      // ���j�[�N���ŋ��L�o�^

		}


	}

	void GameStage::CreateEnemy()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(9.0f,9.0f,-0.001f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-35.0f,26.25f,-0.5f)
		}
		};
		for (auto& v : vec) {

			auto ptrEnemy = AddGameObject<Enemy>(v[0], v[1], v[2]);

		}
	}


	//�S�[��
	void GameStage::CreategoalGate()
	{

		//auto ptrgoalGate = AddGameObject<goalGate>(& scale,& rotation,& position);
		//SetSharedGameObject(L"Goal", ptrgoalGate);
		//ptrgoalGate->AddTag(L"Goal");

		vector< vector <Vec3> > vec = {
		{
			Vec3(0.0f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-4.7f,0.005f,30.0f)
		}
		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
			AddGameObject<startGate>(v[0], v[1], v[2]);
		}
	}

	//�`�[�Y
	void GameStage::CreateCheese()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(1.0f,1.0f,0.5f),
			Vec3(0.0f,0.0f + XMConvertToRadians(270),0.0f),
			Vec3(-40.0f,0.80f,-0.5f)

		}
		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
			AddGameObject<Cheese>(v[0], v[1], v[2]);
		}
	}


	void GameStage::CreateBox()
	{
		vector<vector<Vec3>> vec = {
		{
			Vec3(2.5f, 2.5f, 2.5f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f ,-4.75f, -4.0f)
		},
			//{
			//	Vec3(2.5f, 2.5f, 2.5f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, -4.75f, -7.0f)
			//}


		};

		int index = 0; // ���j�[�N���p�̃C���f�b�N�X
		vector<shared_ptr<Box>> box; // �������� `Box` ���Ǘ����郊�X�g

		for (auto& v : vec) {
			auto ptrBox = AddGameObject<Box>(v[0], v[1], v[2]);

			// ���j�[�N���𐶐�
			wstring uniqueTag = L"Box_" + to_wstring(index);

			ptrBox->AddTag(uniqueTag);  // ���j�[�N�ȃ^�O��K�p
			box.push_back(ptrBox);    // `Box` �����X�g�ɕۑ�

			index++; // ���̃I�u�W�F�N�g�̂��߂ɃC���f�b�N�X�𑝉�
		}

		// ���ׂĂ� `Box` �����L�Q�[���I�u�W�F�N�g�Ƃ��ēo�^
		for (size_t i = 0; i < box.size(); ++i) {
			wstring uniqueName = L"Box_" + to_wstring(i);  // ���j�[�N���𐶐�
			SetSharedGameObject(uniqueName, box[i]);      // ���j�[�N���ŋ��L�o�^
		}

		//auto ptrBox = AddGameObject<Box>();
		//SetSharedGameObject(L"Box", ptrBox);

	}



	void GameStage::OnCreate() {
		try {

			LoadTextures();
			LoadModels();

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�ǂ̍쐬
			CreateWall();
			//�X�e�[�W�̍쐬
			CreateGround();

			AddGameObject<ShadowFloor>(
				Vec3(100.0f, 50.0f, 2.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-65.0f, -3.0f, 0.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(100.0f, 50.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(85.0f, -3.0f, 0.0f)
			);


			AddGameObject<Table>(
				Vec3(3.0f, 6.0f, 1.0f),
				Vec3(0.0f, XM_PIDIV2, 0.0f),
				Vec3(10.0f, -6.0f, -25.0f)
			);


			//Box�̍쐬
			CreateBox();

			//CreateTestShadowBox();

			//SpotLight�̍쐬
			auto spotLight = AddGameObject<SpotLight>();
			SetSharedGameObject(L"SpotLight", spotLight);
			//�e�̍쐬
			AddGameObject<ShadowObject>();
			//�v���C���[�̍쐬
			CreatePlayer();
			//�G�l�~�[�̍쐬
			CreateEnemy();
			//�X�^�[�g�̍쐬
			CreatestartGate();
			//�S�[���̍쐬
			//CreategoalGate();
			AddGameObject<goalGate>(
				Vec3(1.5f, 1.5f, 0.001f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(45.0f, 22.75f, -0.1f)
			);
			//�`�[�Y�̍쐬
			CreateCheese();

			//�X�v���C�g�I�u�W�F�N�g
			AddGameObject<Phase1>();

			auto UI = AddGameObject<GameStageUI>();
			UI->SetTexture(L"TEX_GameStageUI");
			UI->SetPosition(0, 290.0f, 0);
			UI->SetScale(1.5f, 1.0f, 1.0f);
			m_gameStageUI.push_back(UI);


			auto buttonUI = AddGameObject<GameStageUI>();
			buttonUI->SetTexture(L"TEX_GameButtonUI");
			buttonUI->SetPosition(520.0f, -320.0f, 0);
			buttonUI->SetScale(0.5f, 0.6f, 1.0f);
			m_gameStageUI.push_back(buttonUI);

			auto stage = AddGameObject<GameStageUI>();
			stage->SetTexture(L"TEX_STAGE1");
			stage->SetPosition(0, 0, 0);
			stage->SetScale(2.0f, 2.0f, 1.0f);
			stage->SetColor(1.0f, 1.0f, 1.0f, 0.5f);
			m_gameStageUI.push_back(stage);


			auto scene = App::GetApp()->GetScene<Scene>();
			auto volume = scene->m_volumeBGM;

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Gamebgm", XAUDIO2_LOOP_INFINITE, volume);

			m_pauseManager = AddGameObject<PauseManager>();
		}
		catch (...) {
			throw;
		}
	}
	void GameStage::OnUpdate()
	{

		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<GameStage>());


		auto& app = App::GetApp();

		auto device = app->GetInputDevice();
		auto pad = device.GetControlerVec()[0];
		auto delta = app->GetElapsedTime();

		auto scene = app->GetScene<Scene>();
		wstring log = scene->GetDebugString();
		wstringstream wss(log);


		m_Time += delta;

		if (m_Time > 0.3f && !m_isStageFadingOut)
		{
			m_isStageFadingOut = true;
		}

		if (m_isStageFadingOut)
		{
			//�X�v���C�g���L���ŁA�܂��\������Ă�����
			auto stageSpr = m_gameStageUI[2].lock();
			if (stageSpr && stageSpr->IsDrawActive())
			{
				//�A�j���[�V�����ɂ����鎞��
				const float fadeOutDuration = 0.5f;
				m_fadeTimer += delta;

				if (m_fadeTimer < fadeOutDuration)
				{
					//�A�j���[�V�����̐i����(0.0����1,0)���v�Z
					float progress = m_fadeTimer / fadeOutDuration;
					if (progress > 1.0f)//progress��1.0�𒴂��Ȃ��悤��
					{
						progress = 1.0f;
					}

					float startScaleX = 2.0f;
					float endScaleX = 2.2f;
					float startScaleY = 2.0f;
					float endScaleY = 2.2f;

					float easedProgress = 1.0f - pow(1.0f - progress, 2.0f); // 2��͊ɂ₩�ȃJ�[�u

					float currentScaleX = startScaleX + (endScaleX - startScaleX) * easedProgress;
					float currentScaleY = startScaleY + (endScaleY - startScaleY) * easedProgress;

					stageSpr->SetScale(currentScaleX, currentScaleY, 1.0f);

					float currentAlpha = 1.0f - progress;
					stageSpr->SetColor(1.0f, 1.0f, 1.0f, currentAlpha);


					wss << L"Delta: " << delta << L"\n";
					wss << L"Timer: " << m_fadeTimer << L"\n";
					wss << L"Progress: " << progress << L"\n";
					wss << L"Alpha: " << currentAlpha << L"\n";
				}
				else
				{
					stageSpr->SetDrawActive(false);
				}
			}
		}

	}

	void GameStage::OnPushA()
	{

	}


	//// �e�N�X�`���̓Ǎ�
	void GameStage::LoadTextures()
	{
		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp(); // �A�v���P�[�V�����I�u�W�F�N�g(�V���O���g��)�̃C���X�^���X���擾����

		// ���f�B�A�t�H���_�̎擾
		auto mediaPath = app->GetDataDirWString();

		// �e�N�X�`���t�H���_�̒�`
		auto texPath = mediaPath + L"Textures\\";

		// �T�E���h�t�H���_�̒�`
		auto soundPath = mediaPath + L"Sounds\\";

		// �e�N�X�`���̓Ǎ��Ɠo�^
		//app->RegisterTexture(L"TEX_BOX", texPath + L"brick.jpg");
		app->RegisterTexture(L"TEX_CHEESE", texPath + L"cheese.png");
		app->RegisterTexture(L"TEX_KABE", texPath + L"kabe.jpg");
		app->RegisterTexture(L"TEX_YUKA", texPath + L"floor.png");
		app->RegisterTexture(L"TEX_PAUSE", texPath + L"PauseSprite.png");
		app->RegisterTexture(L"TEX_NEZUMI", texPath + L"nezumi.png");
		app->RegisterTexture(L"TEX_NEZUMI2", texPath + L"nezumi2.png");
		app->RegisterTexture(L"TEX_SHELF", texPath + L"Shelf.png");
		app->RegisterTexture(L"TEX_ENEMY", texPath + L"Cat.png");
		app->RegisterTexture(L"TEX_START", texPath + L"Goal.png");
		app->RegisterTexture(L"TEX_GOAL", texPath + L"Goal.png");
		app->RegisterTexture(L"TEX_BbuttondeGameStart", texPath + L"BbuttondeGameStart.png");
		app->RegisterTexture(L"TEX_RESTART", texPath + L"PauseStage restart.png");
		app->RegisterTexture(L"TEX_BACK", texPath + L"PauseStage title.png");
		app->RegisterTexture(L"TEX_SETTING", texPath + L"PauseStage setting.png");
		app->RegisterTexture(L"TEX_END", texPath + L"PauseStage end.png");
		app->RegisterTexture(L"TEX_END2", texPath + L"PauseStage Back.png");

		app->RegisterTexture(L"TEX_GameStageUI", texPath + L"GameStageUI.png");
		app->RegisterTexture(L"TEX_GameButtonUI", texPath + L"GameButtonUI.png");
		app->RegisterTexture(L"TEX_Filter", texPath + L"Filter.png");


	}

	void GameStage::LoadModels()
	{
		auto& app = App::GetApp();

		auto mediaPath = app->GetDataDirWString();

		auto modelPath = mediaPath + L"Models\\";


		//�����v
		if (app->CheckResource<MeshResource>(L"MODEL_LAMP")) return;
		auto meshLamp = MeshResource::CreateStaticModelMesh(modelPath + L"Lamp\\", L"NyauNyauLamp.bmf");
		app->RegisterResource(L"MODEL_LAMP", meshLamp);


		//�e�[�u��
		if (app->CheckResource<MultiMeshResource>(L"MODEL_TABLE")) return;
		auto meshTable = MultiMeshResource::CreateStaticModelMultiMesh(modelPath + L"Table\\", L"Table.bmf");
		app->RegisterResource(L"MODEL_TABLE", meshTable);


		//�݂�(��)
		if (app->CheckResource<MeshResource>(L"MODEL_TSUMIKI1")) return;
		auto meshTsumiki1 = MeshResource::CreateBoneModelMesh(modelPath + L"Block1\\", L"Block1.bmf");
		app->RegisterResource(L"MODEL_TSUMIKI1", meshTsumiki1);

	}


	void GameStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);

	}

	void GameStage::OnUpdate2()
	{
		/*	auto& app = App::GetApp();
			MainCamera* mainCam = app->*/

		if (currentPhase == GamePhase::Phase1)
		{

			auto pause = m_pauseManager.lock();
			if (!pause)
			{
				return;
			}

			if (pause->IsPlaying())
			{
				auto gameObjectVec = GetGameObjectVec();
				for (auto obj : gameObjectVec)
				{

					/*if (gameObjectVec.empty())
					{
						std::cout << "GetGameObjectVec() �ɂ���Ď擾���ꂽ�I�u�W�F�N�g�̃��X�g����ł��B" << std::endl;
						return;
					}*/
					if (dynamic_pointer_cast<PauseManager>(obj))
					{
						obj->SetUpdateActive(true);
					}

					if (dynamic_pointer_cast<Box>(obj)) //dynamic_pointer_cast<Box>(obj) 
					{
						obj->SetUpdateActive(true);
					}
					else if (dynamic_pointer_cast<ShadowObject>(obj))
					{
						obj->SetUpdateActive(true);
					}
					else
					{
						obj->SetUpdateActive(false);
					}


				}



				auto pause = m_pauseManager.lock();
				if (!pause)
				{
					return;
				}

				// B�{�^����Phase2(GameStart)��
				auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
				{
					SetView(m_mainView);

					currentPhase = GamePhase::Phase2;

					auto UI = m_gameStageUI[0].lock();
					UI->SetDrawActive(false);

					auto gameObjectVec = GetGameObjectVec();
					for (auto obj : gameObjectVec)
					{
						if (dynamic_pointer_cast<Box>(obj))
						{
							obj->SetUpdateActive(false);
						}
						else
						{
							obj->SetUpdateActive(true);

						}
					}



				}
			}

		}
	}
}
	
//end basecross
