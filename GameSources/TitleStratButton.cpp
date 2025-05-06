/*!
@file TitleStartButton.cpp
@brief �X�^�[�g�{�^�� �X�v���C�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//������
	void TitleStartButton::OnCreate()
	{
		// ���_(Vertex)�f�[�^��ݒ�
		Col4 color(1, 1, 1, 1);
		std::vector<VertexPositionColorTexture> vertices = {
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
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // ���_�f�[�^�ƃC���f�b�N�X�f�[�^��ݒ肷��
		drawComp->SetTextureResource(L"TEX_TITLESTRATBUTTON");
		SetAlphaActive(true);

		// �ʒu��ݒ肷��
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0, -260, 0); // ��ʂ̒��S�����_�Ƃ����s�N�Z���P�ʁi1280x800�j
	}

	void TitleStartButton::OnUpdate()
	{
		//// �A���t�@�l��ύX���ē_�ł�����
		//static float time = 0.0f;
		//time += 0.1f; // ���Ԃ̐i�s
		//float alpha = (sin(time) + 1.0f) * 0.5f; // sin�g���g���ăA���t�@�l��ω�

		//auto drawComp = GetComponent<PCTSpriteDraw>();
		//drawComp->SetAlpha(alpha);

		auto& app = App::GetApp();
		//�o�ߎ��Ԃ��擾
		float elapsedTiem = app->GetElapsedTime();
		//�ݐώ��Ԃ�ێ�
		static float accumulatedTime = 0.0f;
		accumulatedTime += elapsedTiem;//�o�ߎ��Ԃ����Z

		//�A���t�@�n�̕ύX���v�Z
		float alpha = (sin(accumulatedTime) + 1.0f) * 0.5f;

		auto drawComp = GetComponent<PCTSpriteDraw>();
		drawComp->SetAlpha(alpha);
	
	}


}
//end basecross
