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

		//���݃Z���N�g����Ă���X�e�[�W�i���o�[
		int m_StageNum;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		
		float m_volumeBGM;
		float m_volumeLevelBGM;

		float m_volumeSE;
		float m_volumeLevelSE;

		//Pause�̏���
		Scene() :
			SceneBase(),
			m_volumeBGM(0.50f),
			m_volumeLevelBGM(0.0f),
			m_volumeSE(0.50f),
			m_volumeLevelSE(0.0f)

		{}


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
