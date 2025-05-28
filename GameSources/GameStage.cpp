
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
		// �J�����̐ݒ�
		auto mainCamera = ObjectFactory::Create<MainCamera>();
		auto phase1Camera = ObjectFactory::Create<Phase1Camera>();
		phase1Camera->SetEye(Vec3(50.0f, 15.0f, 5.0f));
		phase1Camera->SetAt(Vec3(-5.0f, -5.0f, 5.0f));

		// �J�����ւ̎Q�Ƃ�ێ����Ă���
		m_mainCamera = mainCamera;
		m_phase1Camera = phase1Camera; 

		// �r���[�ɃJ������ݒ�
		auto view = CreateView<SingleView>();
		if (currentPhase == GamePhase::Phase1)
			view->SetCamera(m_mainCamera);
		if (currentPhase == GamePhase::Phase2)
			view->SetCamera(m_mainCamera);



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
			//{
			//	Vec3(30.0f, 10.0f, 1.0f), 
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(0.0f, 4.0f, 5.0f)
			//},
			{
				Vec3(100.0f, 50.0f, 1.0f),
				Vec3(0.0f, -XM_PI / 2, 0.0f),
				Vec3(-5.0f, 4.0f, 0.0f)
			},

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
			Vec3(50.0f, 10.0f, 100.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(19.0f, -10.5f, 0.0f)
		},
			//{
			//	Vec3(20.0f, 1.0f, 8.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-8.0f, -1.0f, 6.0f)
			//},
			//{
			//	Vec3(8.0f, 1.0f, 20.0f),
			//	Vec3(0.0f,  0.0f, 0.0f),
			//	Vec3(0.0f, -1.0f, 6.0f)

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
			Vec3(1.0f, 20.0f, 20.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(-5.0f, -10.5f, -30.0f)
		},
			//{
			//	Vec3(20.0f, 1.0f, 8.0f),
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-8.0f, -1.0f, 6.0f)
			//},
			//{
			//	Vec3(8.0f, 1.0f, 20.0f),
			//	Vec3(0.0f,  0.0f, 0.0f),
			//	Vec3(0.0f, -1.0f, 6.0f)

			//}

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


	//�X�^�[�g
	void GameStage::CreatestartGate()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.0f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-4.7f,0.005f,-40.0f)
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
				Vec3(3.75f, 3.0f, 3.0f),
				Vec3(0.0f, 0.0f + XMConvertToRadians(270) , 0.0f),
				Vec3(-4.75f, 1.0f, -40.0f)
			},
			//{
			//	Vec3(0.0f, 0.25f, 0.25f),
			//	Vec3(0.0f, 90.0f, 0.0f),
			//	Vec3(-8.0f, 0.0f ,4.0f)
			//}

		};

		int index = 0; // ���j�[�N���p�̃C���f�b�N�X
		vector<shared_ptr<Player>> players; // �������� `Player` ���Ǘ����郊�X�g

		for (auto& v : vec)
		{
			auto ptrPlayer = AddGameObject<Player>(v[0], v[1], v[2]);
			m_mainCamera->SetTargetObject(ptrPlayer);

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
			Vec3(-0.01f,9.0f,9.0f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-4.7f,4.0f,-50.0f)
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
		vector< vector <Vec3> > vec ={
		{
			Vec3(1.0f,1.0f,0.5f),
			Vec3(0.0f,0.0f + XMConvertToRadians(270),0.0f),
			Vec3(-4.6f,3.0f,-5.0f)

		}
	    };
	    //�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
			AddGameObject<Cheese>(v[0], v[1], v[2]);
		}
	}


	void GameStage::CreateBox()
	{

		auto ptrBox = AddGameObject<Box>();
		SetSharedGameObject(L"Box", ptrBox);
		//�^�O������
		//ptrBox->AddTag(L"Box");
	}


	//void GameStage::Initialize()
	//{





		// Box�I�u�W�F�N�g�Ƒ��̃Q�[���I�u�W�F�N�g���Z�b�g�A�b�v
		//boxObject = std::make_shared<GameObject>();
		//gameObjects.push_back(boxObject);

		// Phase1 �ł� Box �ȊO���Œ�
		//for (auto& obj : gameObjects) 
		//{
		//	if (obj != boxObject) {
		//		obj->SetUpdateActive(true);
		//		obj->;
		//	}
		//}


	//}


	//void GameStage::CreateTestShadowBox()
	//{
	//	vector<vector<Vec3>> vec =
	//	{
	//		{
	//			Vec3(0.0f, 0.5f, 0.5f),
	//			Vec3(0.0f, 0.0f, 0.0f),
	//			Vec3(-4.75f, 1.2f, -7.0f)
	//		},

	//	};

		//int index = 0; // ���j�[�N���p�̃C���f�b�N�X
		//vector<shared_ptr<TestShadowBox>> TestShadowBoxs; // �������� `` ���Ǘ����郊�X�g

		//for (auto& v : vec)
		//{
		//	auto ptrTestShadowBox = AddGameObject<TestShadowBox>(v[0], v[1], v[2]);

		//	// ���j�[�N���𐶐�
		//	wstring uniqueTag = L"TestShadowBox_" + to_wstring(index);

		//	ptrTestShadowBox->AddTag(uniqueTag);  // ���j�[�N�ȃ^�O��K�p
		//	TestShadowBoxs.push_back(ptrTestShadowBox);    // `` �����X�g�ɕۑ�
		//	index++; // ���̃I�u�W�F�N�g�̂��߂ɃC���f�b�N�X�𑝉�		

		//}

		//// ���ׂĂ� `` �����L�Q�[���I�u�W�F�N�g�Ƃ��ēo�^
		//for (size_t i = 0; i < TestShadowBoxs.size(); i++)
		//{
		//	wstring uniqueName = L"TestShadowBox_" + to_wstring(i);  // ���j�[�N���𐶐�
		//	SetSharedGameObject(uniqueName, TestShadowBoxs[i]);      // ���j�[�N���ŋ��L�o�^

		//}



	//}


	void GameStage::OnCreate() {
		try {

			LoadTextures();

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�ǂ̍쐬
			CreateWall();
			//�X�e�[�W�̍쐬
			CreateGround();

			//�X�e�[�W�̌�����(�K�`�G�X�N���v�g�̂��ߌ�ŏ���)
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 20.0f, 40.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, -10.5f, -30.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 10.0f, 40.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, 10.5f, -30.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 50.0f, 100.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, 35.5f, 0.0f)
			);

			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 20.0f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, -8.5f, -5.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 15.0f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, -8.5f, 5.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 17.0f, 5.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, -8.5f, 15.0f)
			);
			AddGameObject<ShadowFloor>(
				Vec3(1.0f, 20.0f, 20.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-5.0f, -8.5f, 25.0f)
			);







			//AddGameObject<ShadowFloor>(
			//	Vec3(1.0f, 20.0f, 40.0f),  
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-5.0f, -8.5f, 20.0f)
			//);


			//AddGameObject<ShadowFloor>(
			//	Vec3(1.0f, 20.0f, 10.0f),  // 10,1,10
			//	Vec3(0.0f, 0.0f, 0.0f),
			//	Vec3(-5.0f, -9.5f, -5.0f)
			//);






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
				Vec3(0.01f, 2.5f, 1.5f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-4.7f, 2.0f, 25.0f)
			);
			//�`�[�Y�̍쐬
			CreateCheese();

			//�X�v���C�g�I�u�W�F�N�g
			AddGameObject<Phase1>();


			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Gamebgm", XAUDIO2_LOOP_INFINITE, 0.1f);


			// �Q�[���J�n���̃t�F�[�Y�ݒ�
			currentPhase = GamePhase::Phase1;

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

		//�X�^�[�g�{�^�����������Ƃ��Ƀ{�[�Y����
		if (pad.wPressedButtons & XINPUT_GAMEPAD_START)
		{

			auto scene = App::GetApp()->GetScene<Scene>();
			scene->PauseGame();
			m_PauseFlag = !m_PauseFlag;

			if (m_PauseFlag)
			{

				m_Pause = AddGameObject<pauseSprite>();
				m_pauseSprite = true;
			}
			else
			{
				if (m_pauseSprite)
				{
					RemoveGameObject<pauseSprite>(m_Pause);
					m_pauseSprite = false;
				}
				m_PauseFlag = false;
			}
		}

	}

	//�^�C�g���ɖ߂�
	void GameStage::OnPushA()
	{
		if (m_PauseFlag)
		{
			auto scene = App::GetApp()->GetScene<Scene>();
			PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");

			//��莞�Ԍ�ɃX�v���C�g���폜����i�^�C�g����ʂ���Q�[���X�e�[�W�Ɉڂ�^�C�~���O�j
			PostEvent(5.0f, GetThis<ObjectInterface>(), scene, L"RemoveSprite");

		}
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
		app->RegisterTexture(L"TEX_PAUSE", texPath + L"pauseSprite.png");
		app->RegisterTexture(L"TEX_NEZUMI", texPath + L"nezumi.png");
		app->RegisterTexture(L"TEX_NEZUMI2", texPath + L"nezumi2.png");
		app->RegisterTexture(L"TEX_SHELF", texPath + L"Shelf.png");
		app->RegisterTexture(L"TEX_ENEMY", texPath + L"Cat.png");
		app->RegisterTexture(L"TEX_START", texPath + L"Goal.png");
		app->RegisterTexture(L"TEX_GOAL", texPath + L"Goal.png");
		app->RegisterTexture(L"TEX_BbuttondeGameStart", texPath + L"BbuttondeGameStart.png");



	}

	void GameStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);

	}

	void GameStage::SwitchCamera()
	{
		
	}

	void GameStage::OnUpdate2()
	{


		if (currentPhase == GamePhase::Phase1)
		{	

			auto gameObjectVec = GetGameObjectVec();
			for (auto obj : gameObjectVec)
			{

				/*if (gameObjectVec.empty())
				{
					std::cout << "GetGameObjectVec() �ɂ���Ď擾���ꂽ�I�u�W�F�N�g�̃��X�g����ł��B" << std::endl;
					return;
				}*/

				if (obj->FindTag(L"Box")) //dynamic_pointer_cast<Box>(obj) 
				{
					obj->SetUpdateActive(true);
				}
				else
				{
					obj->SetUpdateActive(false);
				}


			}
		}


		// B�{�^����Phase2(GameStart)��
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
		{
			currentPhase = GamePhase::Phase2;



			auto gameObjectVec = GetGameObjectVec();
			for (auto obj : gameObjectVec)
			{
				if (obj->FindTag(L"Box")) //dynamic_pointer_cast<Box>(obj) 
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
	

//end basecross
