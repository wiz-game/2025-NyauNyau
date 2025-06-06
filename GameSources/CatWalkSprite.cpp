/*
@file CatWalkSprite.h
@brief �L�̃X�v���C�g�̎���
*/

#include "stdafx.h"
#include "CatwalkSprite.h"

namespace basecross{

	void CatWalkSprite::OnCreate()
	{
		float texW = 64.0f / 512.0f;
		float texH = 100.0f / 128.0f;
		float left = texW * m_cat;
		float right = left + texW;
		float top = 0.0f;
		float bottom = top + texH;
		m_vertices = {
			{Vec3(0,0,0),m_color,Vec2(left,top)},
			{Vec3(64.0f,0,0),m_color,Vec2(right,top)},
			{Vec3(0,-100.0f,0),m_color,Vec2(left,bottom)},
			{Vec3(64.0f,-100.0f,0),m_color,Vec2(right,bottom)}
		};
		
		// �C���f�b�N�X�f�[�^��ݒ�i���_���Ȃ��鏇�ԁE3�̐��l��g�ɂ��ĎO�p�`�����j
		m_indices = {
			0,1,2,// 1�ڂ̃|���S��(�O�p�`)
			2,1,3 // 2�ڂ̃|���S��(�O�p�`)
		};
		// �X�v���C�g�p�̃h���[�R���|�[�l���g��ǉ�����

		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, m_indices);// ���_�f�[�^�ƃC���f�b�N�X�f�[�^��ݒ肷��
		m_drawComp->SetTextureResource(L"TEX_CatWalk");
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);// �e�N�X�`�����J��Ԃ��悤�ɓ\��t����ݒ�
		SetAlphaActive(true);

		// �ʒu��ݒ肷��
		m_transComp = GetComponent<Transform>();
		m_transComp->SetPosition(550.0f - 64.0f, -300.0f + 50.0f, 0); // ��ʂ̒��S�����_�Ƃ����s�N�Z���P�ʁi1280x800�j
		//m_transComp->SetRotation(0, XM_PI, 0);
		m_transComp->SetScale(1.5f, 1.5f, 1.5f);

	}

	void CatWalkSprite::OnUpdate()
	{
		//�A�j���[�V�������łȂ���΁A�������Ȃ�
		if (!m_isAnimating)
		{
			return;
		}

		m_animationTime += App::GetApp()->GetElapsedTime();

		//�^�C�}�[����R�}�̕\�����Ԃ𒴂�����
		if (m_animationTime >= m_frameDuration)
		{
			m_animationTime = 0.0f;
			m_cat++;//���̃R�}��
			//�Ō�̃R�}�܂ōs������ŏ��̃R�}�ɖ߂�
			if (m_cat >= m_totalFrames)
			{
				m_cat = 0;
			}

			SetCatNum(m_cat);
		}
	}

	//�A�j���[�V�����̊J�n
	void CatWalkSprite::StartAnimation()
	{
		m_isAnimating = true;
		m_animationTime = 0.0f;//�^�C�}�[���Z�b�g
		m_cat = 0;//�ŏ��̃R�}����X�^�[�g
		SetCatNum(m_cat);//�ŏ��̃R�}��\��
	}
	//�A�j���[�V�����̒�~
	void CatWalkSprite::StopAnimation()
	{
		m_isAnimating = false;
	}


	void CatWalkSprite::SetCatNum(int number)
	{
		//�G���[�`���b�N�i���������s������v���O�������~�߂�j
		assert(number >= 0 && number < 8);
		//�Ǘ����Ă���u���l�v���X�V
		m_cat = number;

		//UV���W�ɂ�����A�����ꌅ�̕��ƍ���
		float w = 64.0f / 512.0f;
		float left = w * m_cat;//�����Ŏw�肵�������̍�����\�����W

		//�V�������l�ɍ��킹�āA���_�f�[�^��ύX����
		m_vertices[0].textureCoordinate.x = left;
		m_vertices[1].textureCoordinate.x = left + w;
		m_vertices[2].textureCoordinate.x = left;
		m_vertices[3].textureCoordinate.x = left + w;
		m_drawComp->UpdateVertices(m_vertices);
	}



}