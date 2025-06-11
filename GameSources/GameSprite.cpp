/*!
@file BackTitleButton.cpp
@brief �X�e�[�W�X�v���C�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//������
	void GameSprite::OnCreate()
	{
		// ���_(Vertex)�f�[�^��ݒ�
		Col4 color(0.5f, 0.5f, 0.5f, 0.5f);
		std::vector<VertexPositionColorTexture> vertices = {
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
		m_drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // ���_�f�[�^�ƃC���f�b�N�X�f�[�^��ݒ肷��
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);
		SetAlphaActive(true);

		// �ʒu��ݒ肷��
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetScale(1, 1, 1);
		m_ptrTrans->SetRotation(0, 0, 0);
		m_ptrTrans->SetPosition(0, 0, 0);// ��ʂ̒��S�����_�Ƃ����s�N�Z���P�ʁi1280x800�j
	}

	void GameSprite::OnUpdate()
	{

		if (!m_isMoving)
		{
			return;
		}

		if (m_isMoving)
		{
			// �o�ߎ��Ԃ��擾
			m_totalTime = App::GetApp()->GetElapsedTime();
			Vec3 currentPos = m_ptrTrans->GetPosition();


			// �V����X���W���v�Z
			currentPos.x += m_speed * m_moveDirection * m_totalTime;

			// ���E�`�F�b�N
			// �E�̋��E�𒴂����ꍇ
			if (currentPos.x > 600.0f + m_moveRange)
			{
				currentPos.x = 600.0f + m_moveRange; // ���E�Ɉʒu��␳
				m_moveDirection = -1.0f;      // ���������ɔ��]
			}

			// ���̋��E�𒴂����ꍇ
			else if (currentPos.x < 600.0f - m_moveRange)
			{
				currentPos.x = 600.0f - m_moveRange; // ���E�Ɉʒu��␳
				m_moveDirection = 1.0f;       // �������E�ɔ��]
			}

			// �v�Z��̈ʒu���Đݒ�
			m_ptrTrans->SetPosition(currentPos);
		}
	}

	//�e�N�X�`��
	void GameSprite::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}

	//position
	void GameSprite::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}

	//scale
	void GameSprite::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}

}
//end basecross
