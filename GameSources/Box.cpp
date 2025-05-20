
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
		m_drawComp = AddComponent<PNTStaticDraw>();
		m_drawComp->SetMeshResource(L"DEFAULT_CUBE");
		//drawComp->SetTextureResource(L"TEX_BOX");

		//�g�����X�t�H�[���R���|�[�l���g�擾�Ɛݒ�
		m_transComp = GetComponent<Transform>();
		m_transComp->SetScale(0.5f, 0.5f, 0.5f);
		m_transComp->SetPosition(Vec3(0.0f, -0.25f, 0.0f));

		//�R���W��������
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);

	}

	void Box::OnUpdate()
	{
		float direction = 1.0f; // �ړ������i1.0f:�E�A-1.0f:���j
		float speed = 1.0f; // �ړ����x
		float minX = -2.0f; // �����E
		float maxX = 2.0f; // �E���E

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = m_transComp->GetPosition();

		pos.z += elapsedTime * speed * direction;

		// ���E�𒴂���������𔽓]
		if (pos.z > maxX) {
			pos.z = maxX - (pos.z - maxX); // ���]���̃I�[�o�[�V���[�g��␳
			direction *= -1.0f; // ���ֈړ�
		}
		else if (pos.z < minX) {
			pos.z = minX + (minX - pos.z); // ���]���̃I�[�o�[�V���[�g��␳
			direction *= 1.0f; // �E�ֈړ�
		}
		m_transComp->SetPosition(pos);
		

	}
}
//end basecross
