
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

		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 125.0f, 640.0f, 480.0f));

	}

	void Box::OnUpdate()
	{
		float direction = 1.0f; // �ړ������i1.0f:�E�A-1.0f:���j
		float speed = 1.0f; // �ړ����x
		float minX = -3.0f; // �����E
		float maxX = 3.0f; // �E���E

		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto pos = m_transComp->GetPosition();

		float deltaZ = elapsedTime * speed * direction;

		// **���E�`�F�b�N�̏������C��**
		if (pos.z + deltaZ >= maxX) {
			direction *= -1.0f;
			pos.z = maxX - (deltaZ); // **�������������𔽉f���Đ܂�Ԃ�**
		}
		else if (pos.z + deltaZ <= minX) {
			direction *= -1.0f;
			pos.z = minX + (deltaZ); // **�������������𔽉f���Đ܂�Ԃ�**
		}
		else {
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
}
//end basecross
