/*!
@file MainCamera.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	//������
	void MainCamera::OnCreate()
	{
	}

	// �X�V����
	void MainCamera::OnUpdate()
	{
		// weak_ptr�����b�N���āA�I�u�W�F�N�g�����݂��Ȃ���ΏI������
		auto targetObj = m_targetObj.lock();
		if (!targetObj)
		{
			return;
		}

		auto& app = App::GetApp(); // �A�v���P�[�V�����I�u�W�F�N�g���擾

		float delta = app->GetElapsedTime(); // �o�ߎ��Ԃ��擾

		// �Q�[���p�b�h�I�u�W�F�N�g���擾
		auto& device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0]; // 0�Ԗڂ�I��

		// �I�u�W�F�N�g�ɒǏ]����悤�ɂ���
		auto trans = targetObj->GetComponent<Transform>();
		auto targetPos = trans->GetPosition();

		m_height += pad.fThumbRY * delta;

		m_height -= 10.0f * pad.fThumbRY * delta;
		m_angleY -= XMConvertToRadians(150.0f) * pad.fThumbRX * delta; // �E�X�e�B�b�N�̌X���ɉ����āA�b�ԍő�135����荞��

		Vec3 at = targetPos + Vec3(0.0f, 1.0f, 0.0f);
		Vec3 eye = targetPos + Vec3(cosf(m_angleY) * m_distance, m_height, sinf(m_angleY) * m_distance);

		SetAt(at);
		SetEye(eye);

		// �^�[�Q�b�g�I�u�W�F�N�g���v���C���[��������A�A���O����`����
		auto player = dynamic_pointer_cast<Player>(targetObj);
		if (player)
		{
			player->SetCameraAngleY(m_angleY);
		}
	}
}
//end basecross
