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

			//�X�v���C�g�̐���
			auto sprite = ObjectFactory::Create<Sprite>(500,500);

			//�V�[���ɒǉ�
			auto scene = App::GetApp()->GetScene<Scene>();
			scene->AddObject(sprite);


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
	}

	//�R���g���[���[��A�{�^���ŃQ�[����ʂɈړ�
	void TitleStage::OnPushA()
	{
		auto scene = App::GetApp()->GetScene<Scene>();
		PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToGameStage");
		
		//��莞�Ԍ�ɃX�v���C�g���폜����i�^�C�g����ʂ���Q�[���X�e�[�W�Ɉڂ�^�C�~���O�j
		PostEvent(5.0f, GetThis<ObjectInterface>(), scene, L"RemoveSprite");
	}


	void TitleStage::OnExit()
	{
		auto sprite = ObjectFactory::Create<Sprite>(500,500);
		auto scene = App::GetApp()->GetScene<Scene>();
		scene->RemoveObject(sprite);
	}
}
//end basecross
