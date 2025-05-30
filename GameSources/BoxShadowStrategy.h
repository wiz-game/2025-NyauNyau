#pragma once
#include "stdafx.h"  
#include "Project.h"
#include "BaseShadowStrategy.h"

namespace basecross
{
	class BoxShadowStrategy : public BaseShadowStrategy
	{
	public:
		// �{�b�N�X�̒��_���擾����֐�
		// �{�b�N�X�I�u�W�F�N�g�̒��_���W���擾���A�e�v�Z�Ɏg�p����
		std::vector<Vec3> GetBoxVertices();

		// �e���v�Z����֐��i�I�[�o�[���C�h�j
		// �����̈ʒu�Ɋ�Â��ĉe�̈ʒu���v�Z���A�e�|���S���𐶐�
		std::vector<Vec3> ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& objectVertices) override;

		// �e�̓ʕ���v�Z����֐��i�I�[�o�[���C�h�j
		// �e�̒��_�𐮗����A�œK�ȃ|���S���`��𐶐�
		std::vector<Vec3> ComputeConvexHull(std::vector<Vec3> vertices) override;

		// �ǂƂ̌�_�����߂�֐�
		// �����ƃI�u�W�F�N�g�̒��_����ɁA�Ǐ�ł̉e�̌�_���Z�o
		std::vector<Vec3> ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& objectVertices);

		// �ǂ̕��ʂ𐶐�����֐�
		// �ǂ̖@���Ɗ�_���畽�ʕ��������쐬���A�e�̓��e�v�Z�ɗ��p
		Vec4 GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal);

	};
}
