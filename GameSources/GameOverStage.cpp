/*!
@file Character.cpp
@brief �Q�[���I�[�o�[�X�e�[�W�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���I�[�o�[�X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------

	//�r���[�ƃ��C�g�̍쐬
	void GameOverStage::CreateViewLight() {
		// �J�����̐ݒ�
		auto camera = ObjectFactory::Create<Camera>();
		camera->SetEye(Vec3(0.0f, 5.0f, -15.0f));
		camera->SetAt(Vec3(0.0f, 0.0f, 0.0f));

		// �r���[�ɃJ������ݒ�
		auto view = CreateView<SingleView>();
		view->SetCamera(camera);

		//�}���`���C�g�̍쐬
		auto light = CreateLight<MultiLight>();
		light->SetDefaultLighting(); //�f�t�H���g�̃��C�e�B���O���w��
	}

	void GameOverStage::OnCreate() {
		try {

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//�e�N�X�`���̓Ǎ�
			LoadTextures();

			//�X�v���C�g�I�u�W�F�N�g
			auto Rat = AddGameObject<GameSprite>();
			Rat->SetTexture(L"TEX_Rat");
			Rat->SetPosition(0, 0, 0);
			Rat->SetScale(2.0f, 1.0f, 1.0f);
			m_sprites.push_back(Rat);

			m_sprites.push_back(AddGameObject<GameOverSprite>());
			m_sprites.push_back(AddGameObject<BackTitleButton>());


			m_catSprite = AddGameObject<CatWalkSprite>();
			auto walk = m_catSprite.lock();
			walk->SetDrawActive(false);

			m_loading = AddGameObject<GameSprite>();
			auto loading = m_loading.lock();
			loading->SetTexture(L"TEX_Loading");
			loading->SetPosition(270, -350, 0);
			loading->SetScale(1.0f, 0.5f, 1.0f);
			loading->SetDrawActive(false);

			m_rat = AddGameObject<GameSprite>();
			auto rat = m_rat.lock();
			rat->SetTexture(L"TEX_NEZUMI");
			rat->SetPosition(610.0f, -385.0f, 0);
			rat->SetScale(0.1f, 0.2f, 1.0f);
			rat->SetDrawActive(false);
			rat->SetMovementActive(false);


			auto scene = App::GetApp()->GetScene<Scene>();
			auto volumeBGM = scene->m_volumeBGM;
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, volumeBGM);

		}
		catch (...) {
			throw;
		}

	}


	void GameOverStage::OnUpdate()
	{
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<GameOverStage>());
	}

	//�R���g���[���[��A�{�^���ŃQ�[����ʂɈړ�
	void GameOverStage::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		auto volumeSE = scene->m_volumeSE;
		auto ptrXA = App::GetApp()->GetXAudio2Manager();
		m_SE = ptrXA->Start(L"button_SE", 0, volumeSE);

		StartCatWalkAnimation();
		PostEvent(3.0f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");
	}

	void GameOverStage::LoadTextures()
	{
		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();

		// ���f�B�A�t�H���_�̎擾
		auto mediaPath = app->GetDataDirWString();

		// �e�N�X�`���t�H���_�̒�`
		auto texPath = mediaPath + L"Textures\\";

		// �e�N�X�`���̓Ǎ��Ɠo�^
		app->RegisterTexture(L"TEX_GAMEOVER", texPath + L"GameOver.png");
		app->RegisterTexture(L"TEX_BACKTITLE", texPath + L"Back Title.png");
		app->RegisterTexture(L"TEX_Rat", texPath + L"Rat GameOver.png");

	}

	void GameOverStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}


	void GameOverStage::StartCatWalkAnimation()
	{
		//�X�v���C�g�̔�\��
		for (auto sprite : m_sprites)
		{
			RemoveGameObject<GameObject>(sprite);
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
