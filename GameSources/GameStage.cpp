
/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(10.0f, 20.0f, -8.0f);// 10,20,-8
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
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
				Vec3(30.0f, 10.0f, 1.0f),
				Vec3(0.0f, XM_PI / 2, 0.0f),
				Vec3(-5.3f, 4.0f, 2.0f)
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
			Vec3(10.0f, 1.0f, 30.0f),  // 10,1,10
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f)
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

		for (auto& v : vec) {
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

	//�X�^�[�g
	void GameStage::CreatestartGate()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.7f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-5.3f, 4.0f, 2.0f)
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
				Vec3(0.0f, 0.25f, 0.25f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(-4.75f, 0.0f, -3.0f)
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
			auto ptrPlayer = AddGameObject<Player>(v[0],v[1],v[2]);

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

	//�S�[��
	void GameStage::CreategoalGate()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.7f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(3.0f,0.005f,4.6f)
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
			Vec3(0,0.5,0.5),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-4.75f,0.001f,2.0f)
		}
		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
			AddGameObject<Cheese>(v[0], v[1], v[2]);
		}
	}




	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�ǂ̍쐬
			CreateWall();
			//�X�e�[�W�̍쐬
			CreateGround();
			//Box�̍쐬
			AddGameObject<Box>();
			//SpotLight�̍쐬
			//AddGameObject<SpotLight>();
			//�v���C���[�̍쐬
			CreatePlayer();
			//�X�^�[�g�̍쐬
			CreatestartGate();
			//�S�[���̍쐬
			CreategoalGate();
			//�`�[�Y�̍쐬
			CreateCheese();



		}
		catch (...) {
			throw;
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

		// �e�N�X�`���̓Ǎ��Ɠo�^
		app->RegisterTexture(L"TEX_BOX", texPath + L"brick.jpg");
	}

}
//end basecross
