
/*!
@file BoX.cpp
@brief ���̃I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void Box::OnCreate()
	{
		//�h���[�R���|�[�l���g�̒ǉ��Ɛݒ�
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetTextureResource(L"TEX_BOX");

		//�g�����X�t�H�[���R���|�[�l���g�擾�Ɛݒ�
		auto transComp = GetComponent<Transform>();
<<<<<<< HEAD
		transComp->SetScale(0.5f, 0.5f, 0.5f);
		transComp->SetPosition(Vec3(-4.75f, 0.0f, -4.0f));
=======
		transComp->SetScale(1.0f, 1.0f, 1.0f);
		transComp->SetPosition(Vec3(-1.0f, 0.125f, 0));
>>>>>>> Takumu_Honda-

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

	}

	void Box::OnUpdate()
	{

	}
}
//end basecross
