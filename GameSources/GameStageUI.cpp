/*!
@file BackTitleButton.cpp
@brief �X�e�[�W�X�v���C�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//������
	void GameStageUI::OnCreate()
	{
		// ���_(Vertex)�f�[�^��ݒ�
		Col4 color(1, 1, 1, 1);
		m_vertices = {
			{Vec3(-200, +130, 0), color, Vec2(0, 0)}, // �@
			{Vec3(+200, +130, 0), color, Vec2(1, 0)}, // �A
			{Vec3(-200, -130, 0), color, Vec2(0, 1)}, // �B
			{Vec3(+200, -130, 0), color, Vec2(1, 1)}, // �C
		};

		// �C���f�b�N�X�f�[�^��ݒ�i���_���Ȃ��鏇�ԁE3�̐��l��g�ɂ��ĎO�p�`�����j
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1�ڂ̃|���S��(�O�p�`)
			2, 1, 3  // 2�ڂ̃|���S��(�O�p�`)
		};

		// �X�v���C�g�p�̃h���[�R���|�[�l���g��ǉ�����
		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, indices); // ���_�f�[�^�ƃC���f�b�N�X�f�[�^��ݒ肷��
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);
		m_drawComp->SetBlendState(BlendState::AlphaBlend);//�u�����h�X�e�[�g�i�F�̍������j���u�A���t�@�u�����h�v�ɐݒ�
		SetAlphaActive(true);

		// �ʒu��ݒ肷��
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(1, 1, 1);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(0, 0, 0);// ��ʂ̒��S�����_�Ƃ����s�N�Z���P�ʁi1280x800�j


	}

	void GameStageUI::OnUpdate()
	{
		

	}

	//�e�N�X�`��
	void GameStageUI::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}

	//position
	void GameStageUI::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}

	//scale
	void GameStageUI::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}


	void GameStageUI::SetColor(const Col4& color)
	{
		//�ێ����Ă���S���_�̐F�����X�V
		for (auto& vertex : m_vertices)
		{
			vertex.color = color;
		}
		if (m_drawComp)
		{
			m_drawComp->UpdateVertices(m_vertices);
		}
	}

	void GameStageUI::SetColor(float r, float g, float b, float a)
	{
		SetColor(Col4(r, g, b, a));
	}

}
//end basecross
