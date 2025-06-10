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
			xy.z * xz.y - xy.y * xz.z,  // X成分（左手系に変更）
			xy.x * xz.z - xy.z * xz.x,  // Y成分
			xy.y * xz.x - xy.x * xz.y   // Z成分
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