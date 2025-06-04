/*!
@file Character.cpp
@brief �L�^�C�g���X�e�[�W�̎���
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------

	//�r���[�ƃ��C�g�̍쐬
	void TitleStage::CreateViewLight() {
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

	void TitleStage::OnCreate() {
		try {

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//�e�N�X�`���̓Ǎ�
			LoadTextures();

			//�X�v���C�g�I�u�W�F�N�g
			AddGameObject<BackgroundTitleSprite>();
			AddGameObject<TitleStartButton>();

			//�^�C�g���X�v���C�g�̕\��
			auto title1 = AddGameObject<TitleSprite>();
			title1->SetTexture(L"TEX_TITLE ni");
			title1->SetPosition(-300, 170.0f, 0);
			title1->SetScale(1.8f, 1.8f, 0);
			m_titleSprite.push_back(title1);

			auto title2 = AddGameObject<TitleSprite>();
			title2->SetTexture(L"TEX_TITLE lya");
			title2->SetPosition(-170, 150.0f, 0);
			title2->SetScale(1.4f, 1.4f, 0);
			m_titleSprite.push_back(title2);

			auto title3 = AddGameObject<TitleSprite>();
			title3->SetTexture(L"TEX_TITLE u");
			title3->SetPosition(-40, 170.0f, 0);
			title3->SetScale(1.8f, 1.8f, 0);
			m_titleSprite.push_back(title3);

			auto title4 = AddGameObject<TitleSprite>();
			title4->SetTexture(L"TEX_TITLE ni");
			title4->SetPosition(100, 170.0f, 0);
			title4->SetScale(1.8f, 1.8f, 0);
			m_titleSprite.push_back(title4);

			auto title5 = AddGameObject<TitleSprite>();
			title5->SetTexture(L"TEX_TITLE lya");
			title5->SetPosition(220, 150.0f, 0);
			title5->SetScale(1.4f, 1.4f, 0);
			m_titleSprite.push_back(title5);

			auto title6 = AddGameObject<TitleSprite>();
			title6->SetTexture(L"TEX_TITLE u");
			title6->SetPosition(350, 170.0f, 0);
			title6->SetScale(1.8f, 1.8f, 0);
			m_titleSprite.push_back(title6);

			auto title7 = AddGameObject<TitleSprite>();
			title7->SetTexture(L"TEX_TITLE si");
			title7->SetPosition(-300, -20.0f, 0);
			title7->SetScale(1.8f, 1.8f, 0);
			m_titleSprite.push_back(title7);

			auto title8 = AddGameObject<TitleSprite>();
			title8->SetTexture(L"TEX_TITLE ru");
			title8->SetPosition(-150, -20.0f, 0);
			title8->SetScale(1.8f, 1.8f, 0);
			m_titleSprite.push_back(title8);

			auto title9 = AddGameObject<TitleSprite>();
			title9->SetTexture(L"TEX_TITLE e");
			title9->SetPosition(30, -20.0f, 0);
			title9->SetScale(1.8f, 1.8f, 0);
			m_titleSprite.push_back(title9);

			auto title10 = AddGameObject<TitleSprite>();
			title10->SetTexture(L"TEX_TITLE ltu");
			title10->SetPosition(180, -50.0f, 0);
			title10->SetScale(1.3f, 1.3f, 0);
			m_titleSprite.push_back(title10);

			auto title11 = AddGameObject<TitleSprite>();
			title11->SetTexture(L"TEX_TITLE to");
			title11->SetPosition(300, -15.0f, 0);
			title11->SetScale(1.8f, 1.8f, 0);
			m_titleSprite.push_back(title11);

			//auto volume = m_settingStage.lock()->GetBGM();

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, 1.0f);


			//MessageBox(0, L"�j���E�j���E�V���G�b�g", L"�^�C�g��", 0);
		}
		catch (...) {
			throw;
		}

	}


	void TitleStage::OnUpdate()
	{
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<TitleStage>());


		auto delta = App::GetApp()->GetElapsedTime();
		m_totalTime += delta;


		for (int i = 0; i < spriteCount; ++i)
		{
			m_titleSprite[i]->m_phaseOffset = i * phaseIncrement;

			//m_titleSprite.push_back(m_titleSprite[i]);
		}

		//if (m_totalTime >= 1.0f)
		//{
		//	static int currenSpriteIndex = 0;
		//	if (currenSpriteIndex < spriteCount)
		//	{
		//		m_titleSprite[currenSpriteIndex]->m_phaseOffset = currenSpriteIndex * phaseIncrement;
		//		currenSpriteIndex++;
		//	}
		//}

	}

	//�R���g���[���[��A�{�^���ŃQ�[����ʂɈړ�
	void TitleStage::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		PostEvent(1.3f, GetThis<ObjectInterface>(), scene, L"ToSelectStage");
	}

	void TitleStage::LoadTextures()
	{
		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();

		// ���f�B�A�t�H���_�̎擾
		auto mediaPath = app->GetDataDirWString();

		// �e�N�X�`���t�H���_�̒�`
		auto texPath = mediaPath + L"Textures\\";

		// �e�N�X�`���̓Ǎ��Ɠo�^
		app->RegisterTexture(L"TEX_TITLESTAGE", texPath + L"TitleStage2.png");
		app->RegisterTexture(L"TEX_TITLESTRATBUTTON", texPath + L"TitleStage StratButton.png");
		app->RegisterTexture(L"TEX_TITLE ni", texPath + L"Title ni.png");
		app->RegisterTexture(L"TEX_TITLE lya", texPath + L"Title lya.png");
		app->RegisterTexture(L"TEX_TITLE u", texPath + L"Title u.png");
		app->RegisterTexture(L"TEX_TITLE si", texPath + L"Title si.png");
		app->RegisterTexture(L"TEX_TITLE ru", texPath + L"Title ru.png");
		app->RegisterTexture(L"TEX_TITLE e", texPath + L"Title e.png");
		app->RegisterTexture(L"TEX_TITLE ltu", texPath + L"Title ltu.png");
		app->RegisterTexture(L"TEX_TITLE to", texPath + L"Title to.png");

	}

	void TitleStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

}
//end basecross
