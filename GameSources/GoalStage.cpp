/*!
@file Character.cpp
@brief �S�[���^�C�g���X�e�[�W�̎���
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�S�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------

	//�r���[�ƃ��C�g�̍쐬
	void goalStage::CreateViewLight() {
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

	void goalStage::OnCreate() {
		try {

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//�e�N�X�`���̓Ǎ�
			LoadTextures();

			//�X�v���C�g�I�u�W�F�N�g
			AddGameObject<gameClearSprite>();
			AddGameObject<BackTitleButton>();

			auto scene = App::GetApp()->GetScene<Scene>();
			auto volume = scene->m_volume;

			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			m_BGM = ptrXA->Start(L"GameClearbgm", XAUDIO2_LOOP_INFINITE, volume);


		}

		catch (...) {
			throw;
		}

	}

	void goalStage::OnUpdate()
	{
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<goalStage>());

	}

	//�R���g���[���[��A�{�^���ŃQ�[����ʂɈړ�
	void goalStage::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		PostEvent(1.3f, GetThis<ObjectInterface>(), scene, L"ToTitleStage");
	}

	void goalStage::LoadTextures()
	{
		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();

		// ���f�B�A�t�H���_�̎擾
		auto mediaPath = app->GetDataDirWString();

		// �e�N�X�`���t�H���_�̒�`
		auto texPath = mediaPath + L"Textures\\";

		// �e�N�X�`���̓Ǎ��Ɠo�^
		app->RegisterTexture(L"TEX_GOALSTAGE", texPath + L"GoalStage.png");
		app->RegisterTexture(L"TEX_BACKTITLE", texPath + L"Back Title.png");
	}
	void goalStage::OnDestroy()
	{
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);


	}
}
//end basecross
