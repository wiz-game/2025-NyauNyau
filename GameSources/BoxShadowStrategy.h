#pragma once
#include "stdafx.h"  
#include "Project.h"
#include "BaseShadowStrategy.h"

namespace basecross
{
	class BoxShadowStrategy : public BaseShadowStrategy
	{
	public:
		// ボックスの頂点を取得する関数
		// ボックスオブジェクトの頂点座標を取得し、影計算に使用する
		std::vector<Vec3> GetBoxVertices();

		// 影を計算する関数（オーバーライド）
		// 光源の位置に基づいて影の位置を計算し、影ポリゴンを生成
		std::vector<Vec3> ComputeShadow(const Vec3& lightPos, const std::vector<Vec3>& objectVertices) override;

		// 影の凸包を計算する関数（オーバーライド）
		// 影の頂点を整理し、最適なポリゴン形状を生成
		std::vector<Vec3> ComputeConvexHull(std::vector<Vec3> vertices) override;

		// 壁との交点を求める関数
		// 光源とオブジェクトの頂点を基に、壁上での影の交点を算出
		std::vector<Vec3> ComputeShadowIntersections(const Vec3& lightPos, const std::vector<Vec3>& objectVertices);

		// 壁の平面を生成する関数
		// 壁の法線と基準点から平面方程式を作成し、影の投影計算に利用
		Vec4 GeneratePlane(const Vec3& wallPoint, const Vec3& wallNormal);

	};
}
