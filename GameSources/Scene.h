/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {

		void CreateResourses();

		bool m_isPlaying;

		//���݃Z���N�g����Ă���X�e�[�W�i���o�[
		int m_StageNum;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		
		//Pause�̏���
		Scene() :
			SceneBase(),
			m_isPlaying(true)
		{}

		bool IsPlaying() const
		{
			return m_isPlaying;
		}

		void PlayGame(bool isPause)
		{
			//�u�Q�[�����s���v�t���O��܂�
			m_isPlaying = isPause;

			//�u���݂̃X�e�[�W�v�ɂ��邷�ׂẴQ�[���I�u�W�F�N�g���~������
			auto stage = GetActiveStage();
			auto gameObjects = stage->GetGameObjectVec();
			for (auto& gameObject : gameObjects)
			{
				gameObject->SetUpdateActive(isPause);
			}
		}

		void PauseGame()
		{
			PlayGame(!IsPlaying());
		}

		//�X�e�[�W�i���o�[�̃A�N�Z�T
		int GetStageNum() const
		{
			return m_StageNum;
		}

		void SetStageNum(int i)
		{
			m_StageNum = i;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;


	};

}

//end basecross
