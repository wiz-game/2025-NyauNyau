/*!
@file Sprite.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//������
	void Sprite::OnCreate()
	{
		// ���_(Vertex)�f�[�^��ݒ�
		Col4 color(1, 1, 1, 1);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(-640, +400, 0), color, Vec2(0, 0)}, // �@
			{Vec3(+640, +400, 0), color, Vec2(1, 0)}, // �A
			{Vec3(-640, -400, 0), color, Vec2(0, 1)}, // �B
			{Vec3(+640, -400, 0), color, Vec2(1, 1)}, // �C
		};

		// �C���f�b�N�X�f�[�^��ݒ�i���_���Ȃ��鏇�ԁE3�̐��l��g�ɂ��ĎO�p�`�����j
		std::vector<uint16_t> indices = {
			0, 1, 2, // 1�ڂ̃|���S��(�O�p�`)
			2, 1, 3  // 2�ڂ̃|���S��(�O�p�`)
		};

		// �X�v���C�g�p�̃h���[�R���|�[�l���g��ǉ�����
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices); // ���_�f�[�^�ƃC���f�b�N�X�f�[�^��ݒ肷��

		// �ʒu��ݒ肷��
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(0, 0, 0); // ��ʂ̒��S�����_�Ƃ����s�N�Z���P�ʁi1280x800�j
	}

}
//end basecross
