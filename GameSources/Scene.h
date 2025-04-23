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
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
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
