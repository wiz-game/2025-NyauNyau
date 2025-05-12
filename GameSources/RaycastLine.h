/*!
@file ShadowObject.h
@brief �e�̎Z�o�E�`����s���I�u�W�F�N�g
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	class RaycastLine : public GameObject
	{
		std::shared_ptr<PCStaticDraw> m_draw;

		Vec3 m_startPosition;
		Vec3 m_endPosition;
		Vec3 m_direction;

		Col4 m_startColor;
		Col4 m_endColor;

		//�������b�V���f�[�^
		std::vector<VertexPositionColor> m_vertices;
		std::vector<uint16_t> m_indices;
	public :
		//�R���X�g���N�^
		RaycastLine(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_startPosition(Vec3(0)),
			m_endPosition(Vec3(0)),
			m_direction(Vec3(0)),
			m_startColor(Col4(1.0f, 1.0f, 1.0f, 1.0f)),
			m_endColor(Col4(1.0f, 1.0f, 1.0f, 1.0f))
		{
		}

		virtual ~RaycastLine()
		{
		}

		void OnCreate() override;//����
		//void OnUpdate() override;

		//���̎n�_�ƏI�_������Ă���
		void SetLinePosition(const Vec3& startPosition, const Vec3& endPosition)
		{
			m_startPosition = startPosition;
			m_endPosition = endPosition;
			m_direction = endPosition - startPosition;
			m_direction = m_direction.normalize();

			//���b�V���f�[�^�̍X�V
			m_vertices = {
				{m_startPosition,m_startColor},
				{m_endPosition,m_endColor}
			};

			m_draw->UpdateVertices(m_vertices);
		}

	};

}
