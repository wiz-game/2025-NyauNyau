#include"stdafx.h"
#include"Project.h"
#include"BaseShadowStrategy.h"

namespace basecross
{

	Vec3 BaseShadowStrategy::Cross(const Vec3& x, const Vec3& y, const Vec3& z)
	{
		Vec3 xy = y - x;
		Vec3 xz = z - x;

		return Vec3(
			xy.z * xz.y - xy.y * xz.z,  // X成分（左手系に変更）
			xy.x * xz.z - xy.z * xz.x,  // Y成分
			-(xy.y * xz.x - xy.x * xz.y)   // Z成分
		);

	}

	void BaseShadowStrategy::BubbleSort(std::vector<Vec3>& vertices)
	{
		for (size_t i = 0; i < vertices.size() - 1; ++i)
		{
			for (size_t j = 0; j < vertices.size() - i - 1; ++j)
			{
				//X → Y → Z の順でソート
				if (vertices[j].z > vertices[j + 1].z ||
					(vertices[j].z == vertices[j + 1].z && vertices[j].y > vertices[j + 1].y) ||
					(vertices[j].z == vertices[j + 1].z && vertices[j].y == vertices[j + 1].y && vertices[j].x > vertices[j + 1].x))
				{
					std::swap(vertices[j], vertices[j + 1]);
				}
			}
		}
	}

}