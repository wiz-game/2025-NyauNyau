/*!
@file BackTitleButton.cpp
@brief �X�^�[�g�{�^�� �X�v���C�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//������
	void BackTitleButton::OnCreate()
	{
		// ���_(Vertex)�f�[�^��ݒ�
		Col4 color(1, 1, 1, 1);
		m_vertices = {
			{Vec3(-200, +100, 0), color, Vec2(0, 0)}, // �@
			{Vec3(+200, +100, 0), color, Vec2(1, 0)}, // �A
			{Vec3(-200, -100, 0), color, Vec2(0, 1)}, // �B
			{Vec3(+200, -100, 0), color, Vec2(1, 1)}, // �C
		};

		// �C���f�b�N�X�f�[�^��ݒ�i���_���Ȃ��鏇�ԁE3�̐��l��g�ɂ��ĎO�p�`�����j
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1�ڂ̃|���S��(�O�p�`)
			2, 1, 3  // 2�ڂ̃|���S��(�O�p�`)
		};

		// �X�v���C�g�p�̃h���[�R���|�[�l���g��ǉ�����
		auto drawComp = AddComponent<PCTSpriteDraw>(m_vertices, indices); // ���_�f�[�^�ƃC���f�b�N�X�f�[�^��ݒ肷��
		drawComp->SetTextureResource(L"TEX_TITLESTRATBUTTON");
		drawComp->SetSamplerState(SamplerState::LinearWrap);
		SetAlphaActive(true);

		// �ʒu��ݒ肷��
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(1, 1, 1);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(0, -260.0f, 0);// ��ʂ̒��S�����_�Ƃ����s�N�Z���P�ʁi1280x800�j
	}

	void BackTitleButton::OnUpdate()
	{
		//�o�ߎ��Ԃ��擾
		float elapsedTiem = App::GetApp()->GetElapsedTime();

		//���Ԍo��
		m_totalTime += elapsedTiem;
		if (m_totalTime >= XM_PI)
		{
			m_totalTime = 0.0f;
		}

		auto drawComp = GetComponent<PCTSpriteDraw>();
		//���ł̕ω�
		float s = sin(m_totalTime) * 0.75f + 0.25f;
		//���C�g�̓�����
		drawComp->SetDiffuse(Col4(1, 1, 1, s));
	}


}
//end basecross
