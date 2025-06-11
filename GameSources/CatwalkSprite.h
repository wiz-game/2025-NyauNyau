/*!
@file CatWalkSprite.h
@brief �L�̃X�v���C�g
*/

#pragma once
#include "stdafx.h"
namespace basecross {

	//----------------------------------------------------------------------------------------------------
	//class CatWalkSprite : public GameObject;
	//----------------------------------------------------------------------------------------------------

	class CatWalkSprite :public GameObject
	{
		Col4 m_color;
		std::vector<VertexPositionColorTexture> m_vertices;
		std::vector<uint16_t> m_indices;
		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_transComp;
		
		float m_cat;//���݂̃R�}�ԍ�
		float m_isAnimating;//�A�j���[�V���������ǂ����̃t���O
		float m_animationTime;//�A�j���[�V�����̌o�ߎ���

		const int m_totalFrames;//�S�S�}��
		const float m_frameDuration;//��R�}�̕\������


	public:
		//�\�z�Ɣj��
		CatWalkSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_color(1,1,1,1),
			m_cat(0),
			m_animationTime(0.0f),
			m_isAnimating(false),
			m_totalFrames(8),
			m_frameDuration(0.1f)
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetCatNum(int number);
		void StartAnimation();//�A�j���[�V�������J�n����
		void StopAnimation();//�A�j���[�V�������~�߂�
		
		bool IsCatAnimation()
		{
			return m_isAnimating;
		}

	};

}