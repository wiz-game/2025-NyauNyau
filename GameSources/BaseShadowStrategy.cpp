#include"stdafx.h"
#include"Project.h"
#include"BaseShadowStrategy.h"

namespace basecross
{
	BaseShadowStrategy::BaseShadowStrategy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	}

	Vec3 BaseShadowStrategy::Cross(const Vec3& x, const Vec3& y, const Vec3& z)
	{
		Vec3 xy = y - x;
		Vec3 xz = z - x;

		return Vec3(
			xy.z * xz.y - xy.y * xz.z,  // X�����i����n�ɕύX�j
			xy.x * xz.z - xy.z * xz.x,  // Y����
			xy.y * xz.x - xy.x * xz.y   // Z����
		);

	}

	std::vector<Vec3> BaseShadowStrategy::Sort(std::vector<Vec3> vertices)
	{
		if (vertices.size() < 3) return vertices; // ���_��3�����Ȃ炻�̂܂ܕԂ�

		// �����_���\�[�g
		std::sort(vertices.begin(), vertices.end(), [](const Vec3& a, const Vec3& b) {
			// X���W�Ŕ�r����
			if (a.x != b.x) {
				return a.x < b.x;
			}
			// X���W�������Ȃ�AY���W�Ŕ�r����
			return a.y < b.y;
			});
	}

}