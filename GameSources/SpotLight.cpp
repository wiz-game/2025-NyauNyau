
/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void SpotLight::OnCreate()
	{
		//Col4 color(1.0f, 1.0f, 0.0f, 1.0f);


		//�h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		//�g�����X�t�H�[���R���|�[�l���g�擾�Ɛݒ�
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(0.25f, 0.25f, 0.25f);
		transComp->SetPosition(3.0f, 0.0f, 0.0f);

		//�R���W��������
		//auto ptrColl = AddComponent<CollisionObb>();
		//ptrColl->SetFixed(true);
		//�^�O������
		//AddTag(L"SpotLight");
	}

	void SpotLight::OnUpdate()
	{

	}


}
//end basecross
