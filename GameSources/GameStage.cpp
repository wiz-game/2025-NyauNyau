
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
		const Vec3 eye(10.0f, 10.0f, -15.0f);
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
			{
				Vec3(10.0f, 10.0f, 1.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 4.0f, 5.0f)
			},
			{
				Vec3(15.0f, 10.0f, 1.0f),
				Vec3(0.0f, XM_PI / 2, 0.0f),
				Vec3(-5.3f, 4.0f, 2.0f)
			}
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

	//�X�^�[�g
	void GameStage::CreatestartGate()
	{
		vector< vector <Vec3> > vec = {
		{
			Vec3(0.7f,0.7f,0.5f),
			Vec3(0.0f,0.0f,0.0f),
			Vec3(-3.0f,0.005f,4.6f)
		}
		};
		//�I�u�W�F�N�g�̍쐬
		for (auto v : vec) {
			AddGameObject<startGate>(v[0], v[1], v[2]);
		}
	}
	void GameStage::CreatePlayer()
	{
		auto ptrPlayer = AddGameObject<Player>();
		SetSharedGameObject(L"Player", ptrPlayer);
		ptrPlayer->AddTag(L"Player");

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



	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//�ǂ̍쐬
			CreateWall();
			//�X�e�[�W�̍쐬
			AddGameObject<Ground>();
			//Box�̍쐬
			AddGameObject<Box>();
			//SpotLight�̍쐬
			//AddGameObject<SpotLight>();
			//�v���C���[�̍쐬
			AddGameObject<Player>();
			//�X�^�[�g�̍쐬
			CreatestartGate();
			//�S�[���̍쐬
			CreategoalGate();


			CreatePlayer();
		}
		catch (...) {
			throw;
		}


	}

	//// �e�N�X�`���̓Ǎ�
	//void GameStage::LoadTextures()
	//{
	//	// �A�v���P�[�V�����I�u�W�F�N�g���擾����
	//	auto& app = App::GetApp(); // �A�v���P�[�V�����I�u�W�F�N�g(�V���O���g��)�̃C���X�^���X���擾����

	//	// ���f�B�A�t�H���_�̎擾
	//	auto mediaPath = app->GetDataDirWString();

	//	// �e�N�X�`���t�H���_�̒�`
	//	auto texPath = mediaPath + L"Textures\\";

	//	// �e�N�X�`���̓Ǎ��Ɠo�^
	//	app->RegisterTexture(L"TEX_BOX", texPath + L"brick.jpg");
	//}

}
//end basecross
