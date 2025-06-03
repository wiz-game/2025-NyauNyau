/*!
@file BackTitleButton.cpp
@brief �X�e�[�W�X�v���C�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//������
	void SoundSprite::OnCreate()
	{
		m_width = m_ex - m_sx;
		m_height = m_ey - m_sy;

		// ���_(Vertex)�f�[�^��ݒ�
		Col4 color(1, 1, 1, 1);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(0, 0, 0), color, Vec2(m_sx/1920.0f, m_sy/1080.0f)}, // �@
			{Vec3(m_width, 0, 0), color, Vec2(m_ex/1920.0f, m_sy/1080.0f)}, // �A
			{Vec3(0, -m_height, 0), color, Vec2(m_sx/1920.0f, m_ey/1080.0f)}, // �B
			{Vec3(m_width, -m_height, 0), color, Vec2(m_ex/1920.0f, m_ey/1080.0f)}, // �C
		};

		// �C���f�b�N�X�f�[�^��ݒ�i���_���Ȃ��鏇�ԁE3�̐��l��g�ɂ��ĎO�p�`�����j
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1�ڂ̃|���S��(�O�p�`)
			2, 1, 3  // 2�ڂ̃|���S��(�O�p�`)
		};

		// �X�v���C�g�p�̃h���[�R���|�[�l���g��ǉ�����
		m_drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // ���_�f�[�^�ƃC���f�b�N�X�f�[�^��ݒ肷��
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);
		SetAlphaActive(true);

		// �ʒu��ݒ肷��
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(1, 1, 1);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(0, 0, 0);// ��ʂ̒��S�����_�Ƃ����s�N�Z���P�ʁi1280x800�j
	}

	//�e�N�X�`��
	void SoundSprite::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}

	//position
	void SoundSprite::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}

	//scale
	void SoundSprite::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}

}
//end basecross
