/*!
@file BackgroundTitleSprite.cpp
@brief �Q�[���N���A �X�v���C�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//������
	void TitleSprite::OnCreate()
	{
		// ���_(Vertex)�f�[�^��ݒ�
		Col4 m_color(1, 1, 1, 1);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(-100, +100, 0), m_color, Vec2(0, 0)}, // �@
			{Vec3(+100, +100, 0), m_color, Vec2(1, 0)}, // �A
			{Vec3(-100, -100, 0), m_color, Vec2(0, 1)}, // �B
			{Vec3(+100, -100, 0), m_color, Vec2(1, 1)}, // �C
		};

		// �C���f�b�N�X�f�[�^��ݒ�i���_���Ȃ��鏇�ԁE3�̐��l��g�ɂ��ĎO�p�`�����j
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1�ڂ̃|���S��(�O�p�`)
			2, 1, 3  // 2�ڂ̃|���S��(�O�p�`)
		};

		// �X�v���C�g�p�̃h���[�R���|�[�l���g��ǉ�����
		m_drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // ���_�f�[�^�ƃC���f�b�N�X�f�[�^��ݒ肷��
		SetAlphaActive(true);

		// �ʒu��ݒ肷��
		m_ptrTrans = GetComponent<Transform>();
		m_ptrTrans->SetPosition(0, 0, 0); // ��ʂ̒��S�����_�Ƃ����s�N�Z���P�ʁi1280x800�j
		m_ptrTrans->SetScale(1, 1, 1);

		m_basePosition = m_ptrTrans->GetPosition();
	}
	
	void TitleSprite::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();
		m_totalTime += delta;

		float amplitude = 10.0f;  // sin�g�̕�
		float frequency = 2.0f;   // ����

		// Y�����̃I�t�Z�b�g���T�C���g�Ōv�Z
		float y_offset = amplitude * sinf(m_totalTime * frequency + m_phaseOffset);

		// ���Ƃ��Ƃ̊�ʒu�Ɍv�Z�����I�t�Z�b�g�������āA�V���Ȉʒu�ɐݒ�
		m_ptrTrans->SetPosition(m_basePosition.x, m_basePosition.y + y_offset, m_basePosition.z);

	}

	void TitleSprite::SetTexture(const std::wstring& Key)
	{
		m_drawComp->SetTextureResource(Key);
	}
	void TitleSprite::SetPosition(float x, float y, float z)
	{
		m_ptrTrans->SetPosition(x, y, z);
	}
	void TitleSprite::SetScale(float x, float y, float z)
	{
		m_ptrTrans->SetScale(x, y, z);
	}


}
//end basecross
