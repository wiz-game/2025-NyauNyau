/*!
@file pauseSprite.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//������
	void pauseSprite::OnCreate()
	{
		// ���_(Vertex)�f�[�^��ݒ�
		Col4 color(1, 1, 1, 1);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(-400, +200, 0), color, Vec2(0, 0)}, // �@
			{Vec3(+400, +200, 0), color, Vec2(1, 0)}, // �A
			{Vec3(-400, -200, 0), color, Vec2(0, 1)}, // �B
			{Vec3(+400, -200, 0), color, Vec2(1, 1)}, // �C
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
		m_ptrTrans->SetPosition(0, 0, 0); // ��ʂ̒��S�����_�Ƃ����s�N�Z���P�ʁi1280x800�j
	}

	void pauseSprite::OnUpdate()
	{
		if (m_Selected)
		{
			//���ł̏���
			//�o�ߎ��Ԃ��擾
			float elapsedTime = App::GetApp()->GetElapsedTime();

			//�o�ߎ���
			m_totalTime += elapsedTime * 3;
			if (m_totalTime >= XM_PI)
			{
				m_totalTime = 0.0f;
			}

			//���ł̕ω�
			float s = sin(m_totalTime) * 0.75f + 0.25f;
			//���C�g�̓�����
			m_drawComp->SetDiffuse(Col4(1, 1, 1, s));
		}
		else
		{
			m_drawComp->SetDiffuse(Col4(1, 1, 1, 1));
		}
		
	}

	//�e�N�X�`��
	void pauseSprite::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}
	//position
	void pauseSprite::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}
	//scale
	void pauseSprite::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}

}
//end basecross
