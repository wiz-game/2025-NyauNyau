
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::CreateResourses()
	{
	}
	void Scene::OnCreate(){
		try {


			// �A�v���P�[�V�����I�u�W�F�N�g���擾����
			auto& app = App::GetApp(); // �A�v���P�[�V�����I�u�W�F�N�g(�V���O���g��)�̃C���X�^���X���擾����

			// ���f�B�A�t�H���_�̎擾
			auto mediaPath = app->GetDataDirWString();

			// �T�E���h�t�H���_�̒�`
			auto soundPath = mediaPath + L"Sounds\\";


			app->RegisterWav(L"Titlebgm", soundPath + L"audiostock_864577.wav");
			//app->RegisterWav(L"Gamebgm", soundPath + L"audiostock_1224243.wav");
			app->RegisterWav(L"Gamebgm", soundPath + L"audiostock_1495090.wav");
			app->RegisterWav(L"GameOverbgm", soundPath + L"audiostock_1042193.wav");
			app->RegisterWav(L"GameClearbgm", soundPath + L"audiostock_842617.wav");




			//���\�[�X�쐬
			CreateResourses();

			//�N���A����F��ݒ�
			Col4 Col;
			//Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			Col.set(0.0f, 0.0f, 0.0f, 0.0f);//��
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");

		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}


	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//�ŏ��̃A�N�e�B�u�X�e�[�W�̐ݒ�
			ResetActiveStage<GameStage>();
		}
		//�^�C�g���X�e�[�W�̐ݒ�
		if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		//�S�[���X�e�[�W�̐ݒ�
		if (event->m_MsgStr == L"ToGoalStage") {
			ResetActiveStage<goalStage>();
		}

	}


}
//end basecross
