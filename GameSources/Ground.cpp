
/*!
@file Ground.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Ground::OnCreate()
	{
		// �h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // �L���[�u�^�̃��b�V����ݒ肷��
		drawComp->SetOwnShadowActive(true); // �e���󂯓����

		// �g�����X�t�H�[���R���|�[�l���g�̎擾�Ɛݒ�
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(10, 1, 10); // XZ�����Ɋg�傷��
		transComp->SetPosition(0, -1.0f, 0);

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();


	}

	void Ground::OnUpdate()
	{
	}

}
//end basecross
