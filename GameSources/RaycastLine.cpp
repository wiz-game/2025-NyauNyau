/*!
@file RayCastLine.h
@brief �����𐶐�����
*/

#pragma once
#include "stdafx.h"
#include "Project.h"
#include "RaycastLine.h"

namespace basecross
{
	void RaycastLine::OnCreate()
	{
		//�������\�z�����̒��_�̐ݒ�
		m_vertices = {
			{m_startPosition,m_startColor},
			{m_endPosition,m_endColor}
		};

		//�n�_�ƏI�_���q���C���f�b�N�X
		m_indices = {
			0,1
		};

		//�h���[�R���|�[�l���g�ݒ�
		m_draw = AddComponent<PCStaticDraw>();
		m_draw->SetOriginalMeshUse(true);
		m_draw->CreateOriginalMesh(m_vertices, m_indices);
		auto meshResource = m_draw->GetMeshResource();
		meshResource->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	}
}