
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
		m_transComp->SetPosition(Vec3(0.0f, -0.25f, -4.0f));

		//�R���W��������
		auto ptrColl = AddComponent<CollisionRect>();
		ptrColl->SetFixed(true);

		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 125.0f, 640.0f, 480.0f));

	}


	void Box::OnUpdate()
	{
		auto G = GetStage()->GetThis<GameStage>()->GetGameObjectVec();
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��

		MoveXZ();
		BoxMove();
	}

	Vec2 Box::GetInputState() const {
		Vec2 ret;
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;

		// ���X�e�B�b�N�̏�Ԃ𔻒�
		if (cntlVec[0].bConnected) {
			ret.x = cntlVec[0].fThumbLX;
			ret.y = cntlVec[0].fThumbLY;
		}
		return ret;
	}

	Vec3 Box::GetMoveVector() const
	{
		Vec3 angle(0, 0, 0);
		//���͂̎擾
		auto inPut = GetInputState();
		float moveX = inPut.x;
		float moveZ = inPut.y;

		if (moveX != 0 || moveZ != 0)
		{
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();

			// �v���C���[�̉�]�p���l��
			//float playerRotationY = XMConvertToRadians(m_Rotation.y);

			// �J������������̊p�x
			auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
			front.y = 0;
			front.normalize();
			float frontAngle = -atan2(front.z, front.x);

			// �X�e�B�b�N���͂̊p�x
			Vec2 moveVec(moveX, moveZ);
			float cntlAngle = atan2(-moveX, moveZ);

			// ���v�p�x�v�Z�i�J���� + �X�e�B�b�N + �v���C���[��]�j
			float totalAngle = frontAngle + cntlAngle;

			// �p�x����ړ��x�N�g�����쐬
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			angle.normalize();

			// �ړ��T�C�Y�̓K�p
			angle *= -moveVec.length();

			//y�����Œ�
			angle.y = 0;

			//if (angle.x >= 1.0f)
			//{
			//	angle.z = 0.0f;
			//}
			//else if (angle.z >= 1.0f)
			//{
			//	angle.x = 0.0f;
			//}



		}
		return angle;

		static float direction = 1.0f; // **�֐����Œl��ێ�**
		float speed = 1.0f; // �ړ����x
		float minX = -3.0f; // �����E
		float maxZ = 3.0f; // �E���E

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = m_transComp->GetPosition();

		float deltaZ = elapsedTime * speed * direction;

		// ���E�`�F�b�N���ĕ������]
		if (pos.z + deltaZ >= maxZ)
		{
			direction = -1.0f; // �������]
			pos.z = maxZ; // ���E�𒴂��Ȃ��悤�ɂ���
		}

		else if (pos.z + deltaZ <= minX)
		{
			direction = 1.0f; // �������]
			pos.z = minX; // ���E�𒴂��Ȃ��悤�ɂ���
		}

		else
		{
			pos.z += deltaZ; // �ʏ�̈ړ�
		}

		m_transComp->SetPosition(pos);

		wstring positionStr(L"Position:\t");
		positionStr += L"X=" + Util::FloatToWStr(pos.x, 12, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Y=" + Util::FloatToWStr(pos.y, 12, Util::FloatModify::Fixed) + L",\n";
		positionStr += L"Z=" + Util::FloatToWStr(pos.z, 12, Util::FloatModify::Fixed) + L"\n";
		positionStr += L"direction=" + Util::FloatToWStr(direction, 12, Util::FloatModify::Fixed) + L"\n";
		positionStr += L"deltaZ=" + Util::FloatToWStr(deltaZ, 12, Util::FloatModify::Fixed) + L"\n";
		positionStr += L"ElapssedTime=" + Util::FloatToWStr(elapsedTime, 12, Util::FloatModify::Fixed) + L"\n";

		wstring str = positionStr;


		//������R���|�[�l���g�̎擾
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}


	void Box::MoveXZ() {
		auto angle = GetInputState();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = GetComponent<Transform>()->GetPosition();
		pos += elapsedTime * m_velocity;
		GetComponent<Transform>()->SetPosition(pos);
	}

	void Box::BoxMove()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto angle = GetMoveVector();
		if (angle.length() > 0.0f)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			pos += angle * elapsedTime * 6.0f;
			GetComponent<Transform>()->SetPosition(pos); // �X�V��

		}
	}

}
//end basecross
