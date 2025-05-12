	/*!
@file Character.cpp
@brief �L�^�C�g���X�e�[�W�̎���
*/

#include "stdafx.h"
#include "Project.h"
#pragma once

	namespace basecross {

		//--------------------------------------------------------------------------------------
		//	�Q�[���X�e�[�W�N���X����
		//--------------------------------------------------------------------------------------

		//�r���[�ƃ��C�g�̍쐬
		void StageSelect::CreateViewLight() {
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

		void StageSelect::OnCreate() {
			try {

				//�r���[�ƃ��C�g�̍쐬
				CreateViewLight();

				//�e�N�X�`���̓Ǎ�
				//LoadTextures();

				//auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//m_BGM = ptrXA->Start(L"Titlebgm", XAUDIO2_LOOP_INFINITE, 0.1f);

			}
			catch (...) {
				throw;
			}

		}


		void StageSelect::OnUpdate()
		{
			//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
			m_InputHandler.PushHandle(GetThis<StageSelect>());
		}

		////�R���g���[���[��A�{�^���ŃQ�[����ʂɈړ�
		//void StageSelect::OnPushA()
		//{
		//	auto scene = App::GetApp()->GetScene<Scene>();
		//	PostEvent(0.0f, GetThis<ObjectInterface>(), scene, L"ToGameStage");

		//	//��莞�Ԍ�ɃX�v���C�g���폜����i�^�C�g����ʂ���Q�[���X�e�[�W�Ɉڂ�^�C�~���O�j
		//	PostEvent(5.0f, GetThis<ObjectInterface>(), scene, L"RemoveSprite");
		//}

		void SelectMassege::OnCreate() {
			ChangeWindowMode(true);
			if (DxLib_Init() == -1) return;
			SetFontSize(30);
			currentScene = Scene::Start;  // �����V�[���̐ݒ�
		}

		void SelectMassege::OnUpdate() {
			switch (currentScene) {
			case Scene::Start:
				currentScene = StartScene();
				break;
			case Scene::Init:
				currentScene = GameInit();
				break;
			case Scene::Game:
				currentScene = GameScene();
				break;
			case Scene::End:
				break;
			}
		}
		int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
		{
			SelectMassege selectMassege;
			selectMassege.OnCreate(); // ���������������s

			while (ProcessMessage() == 0 && selectMassege.isRunning()) {
				selectMassege.OnUpdate(); // �V�[���X�V����
				selectMassege.drawScene(); // �`�揈��
			}

			DxLib_End();
			return 0;
		}
		//void StageSelect::OnDestroy() {
		//	//BGM�̃X�g�b�v
		//	auto XAPtr = App::GetApp()->GetXAudio2Manager();
		//	XAPtr->Stop(m_BGM);
		//}

	}
	//end basecross
