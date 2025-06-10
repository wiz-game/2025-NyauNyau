/*!
@file PauseManager.h
@brief �|�[�Y�}�l�[�W���[
*/

#pragma once
#include "stdafx.h"
#include "PauseSprite.h"

namespace basecross {
	//---------------------------------------------------------------------------------------------------------------
	//�|�[�Y�}�l�[�W���[�N���X
	//---------------------------------------------------------------------------------------------------------------

	class PauseManager :public GameObject {
		bool m_isPlaying;//�����Ă邩�ǂ���

		std::vector<std::shared_ptr<PauseSprite>> m_pauseSprites;//�|�[�Y�X�v���C�g�̕ϐ�
		std::shared_ptr<PauseSprite> catPointSprite;//�����
		std::shared_ptr<PauseSprite> Pause;
		shared_ptr<SoundItem> m_SE;


		//�|�[�Y�t���O
		int m_SpriteNum;//���I�����Ă���X�v���C�g


		void ChangeSelect(int num);
		//����Y����ύX������֐�
		void SetSelectPosition(int SpriteNum);
		bool m_CntrolLock;
		float m_selectY;//����Y���W�̈ʒu
		float m_selectX;//����X���W�̈ʒu


	public:

		PauseManager(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_CntrolLock(false),
			m_isPlaying(true),
			m_SpriteNum(0),
			m_selectX(0.0f),
			m_selectY(0.0f)
		{
		}
		virtual ~PauseManager(){}


		bool IsPlaying() const
		{
			return m_isPlaying;
		}

		void PauseManager::PlayGame(bool isPause)
		{
			//�Q�[�����s���̃t���O��܂�
			m_isPlaying = isPause;

			//�u���݂̃X�e�[�W�v�ɂ��邷�ׂẴQ�[���I�u�W�F�N�g���~������
			auto stage = GetStage();
			auto gameObjects = stage->GetGameObjectVec();
			for (auto& gameObject : gameObjects)
			{
				if (dynamic_pointer_cast<PauseManager>(gameObject))
				{
					continue;
				}
				gameObject->SetUpdateActive(isPause);


			}

		}
		void PauseManager::PauseGame();

		virtual void OnCreate() override;//������
		virtual void OnUpdate() override;//�X�V
		virtual void OnDraw() override;//�`��

		//�X�v���C�g�i���o�[�̃A�N�Z�T
		int GetSpriteNum() const
		{
			return m_SpriteNum;
		}

		void SetSpriteNum(int i)
		{
			m_SpriteNum = i;
		}

	};
}

