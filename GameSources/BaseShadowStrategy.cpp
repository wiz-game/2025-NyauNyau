#include"stdafx.h"
#include"Project.h"
#include"BaseShadowStrategy.h"

namespace basecross
{
	BaseShadowStrategy::BaseShadowStrategy(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr)
	{
	}

    Vec3 BaseShadowStrategy::Cross(const Vec3& v1, const Vec3& v2) const
	{
		return Vec3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		);
	}

	std::vector<Vec3> BaseShadowStrategy::Sort(std::vector<Vec3> vertices)
	{
		if (vertices.size() < 3) return vertices; // 頂点が3未満ならそのまま返す

		// ラムダ式ソート
		std::sort(vertices.begin(), vertices.end(), [](const Vec3& a, const Vec3& b) {
			// X座標で比較する
			if (a.x != b.x) {
				return a.x < b.x;
			}
			// X座標が同じなら、Y座標で比較する
			return a.y < b.y;
			});
	}

}