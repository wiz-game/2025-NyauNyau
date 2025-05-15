/*!
@file RayCastLine.h
@brief 光線を生成する
*/

#pragma once
#include "stdafx.h"
#include "Project.h"
#include "RaycastLine.h"

namespace basecross
{
	void RaycastLine::OnCreate()
	{
		//線分を構築する二つの頂点の設定
		m_vertices = {
			{m_startPosition,m_startColor},
			{m_endPosition,m_endColor}
		};

		//始点と終点を繋ぐインデックス
		m_indices = {
			0,1
		};

		//ドローコンポーネント設定
		m_draw = AddComponent<PCStaticDraw>();
		m_draw->SetOriginalMeshUse(true);
		m_draw->CreateOriginalMesh(m_vertices, m_indices);
		auto meshResource = m_draw->GetMeshResource();
		meshResource->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	}
}