#include "Collision.h"

#include "Geometry/AABB.h"
#include "Geometry/OBB.h"
#include "Geometry/Sphere.h"
#include "Math/MathUtility.h"

#include <algorithm>
#include <math/Matrix4x4.h>
#include <math/Vector3.h>

using namespace KamataEngine;
using namespace MathUtility;

namespace Collision {
bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if (aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) {
		if (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) {
			if (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z) {
				return true;
			}
		}
	}

	return false;
}

bool IsCollision(const AABB& aabb, const Sphere& sphere) {
	// 最近接点を求める
	Vector3 closest_point{
	    std::clamp(sphere.center.x, aabb.min.x, aabb.max.x),
	    std::clamp(sphere.center.y, aabb.min.y, aabb.max.y),
	    std::clamp(sphere.center.z, aabb.min.z, aabb.max.z),
	};

	// 最近接点との距離を求める
	if (float distance = Length(closest_point - sphere.center); distance <= sphere.radius) {
		return true;
	}

	return false;
}

bool Collision::IsCollision(const OBB& obb, const Sphere& sphere) {
	// ワールド行列を作成
	Matrix4x4 mat_world = {};
	mat_world.m[0][0] = obb.orientations[0].x;
	mat_world.m[0][1] = obb.orientations[0].y;
	mat_world.m[0][2] = obb.orientations[0].z;
	mat_world.m[0][3] = 0.0f;

	mat_world.m[1][0] = obb.orientations[1].x;
	mat_world.m[1][1] = obb.orientations[1].y;
	mat_world.m[1][2] = obb.orientations[1].z;
	mat_world.m[1][3] = 0.0f;

	mat_world.m[2][0] = obb.orientations[2].x;
	mat_world.m[2][1] = obb.orientations[2].y;
	mat_world.m[2][2] = obb.orientations[2].z;
	mat_world.m[2][3] = 0.0f;

	mat_world.m[3][0] = obb.center.x;
	mat_world.m[3][1] = obb.center.y;
	mat_world.m[3][2] = obb.center.z;
	mat_world.m[3][3] = 1.0f;

	// 逆行列を使用してローカル座標を求める
	Matrix4x4 mat_inverse = InverseMatrix(mat_world);
	Vector3 centerInOBBLocalSpace = Transform(sphere.center, mat_inverse);

	// OBBのサイズからAABBのmin/maxを計算
	Vector3 min = {-obb.size.x, -obb.size.y, -obb.size.z};
	Vector3 max = {obb.size.x, obb.size.y, obb.size.z};
	AABB local_aabb{min, max};

	// 判定
	if (Sphere sphereOBBLocal{centerInOBBLocalSpace, sphere.radius}; IsCollision(local_aabb, sphereOBBLocal)) {
		return true;
	}

	return false;
}

bool IsCollision(const OBB& obb1, const OBB& obb2) {
	/*--- -15本の候補軸を配列に格納 ---*/

	std::array<Vector3, 15> candidate_axes = {
	    // obb1面法線候補軸
	    obb1.orientations[0],
	    obb1.orientations[1],
	    obb1.orientations[2],
	    // obb2面法線候補軸
	    obb2.orientations[0],
	    obb2.orientations[1],
	    obb2.orientations[2],

	    Cross(obb1.orientations[0], obb2.orientations[0]),
	    Cross(obb1.orientations[0], obb2.orientations[1]),
	    Cross(obb1.orientations[0], obb2.orientations[2]),
	    Cross(obb1.orientations[1], obb2.orientations[0]),
	    Cross(obb1.orientations[1], obb2.orientations[1]),
	    Cross(obb1.orientations[1], obb2.orientations[2]),
	    Cross(obb1.orientations[2], obb2.orientations[0]),
	    Cross(obb1.orientations[2], obb2.orientations[1]),
	    Cross(obb1.orientations[2], obb2.orientations[2]),
	};

	// obb同士の中心座標の差
	Vector3 offset = obb2.center - obb1.center;

	for (const auto& raw_axis : candidate_axes) {
		Vector3 axis = raw_axis;
		if (LengthSquared(axis) < 1e-5f) {
			// 外積によって得られた軸の長さがほぼ0の場合はスキップする
			continue;
		}

		axis = Normalize(axis);
		float distance = std::abs(Dot(offset, axis));

		// obb1の投影半径を計算
		float r1 = obb1.size.x * std::abs(Dot(obb1.orientations[0], axis)) + obb1.size.y * std::abs(Dot(obb1.orientations[1], axis)) + obb1.size.z * std::abs(Dot(obb1.orientations[2], axis));
		// obb2の投影半径を計算
		float r2 = obb2.size.x * std::abs(Dot(obb2.orientations[0], axis)) + obb2.size.y * std::abs(Dot(obb2.orientations[1], axis)) + obb2.size.z * std::abs(Dot(obb2.orientations[2], axis));

		// 「中心間距離」が「2つの半径の合計」よりも大きければ、分離軸が存在する
		if (distance > (r1 + r2)) {
			return false;
		}
	}

	return true;
}
} // namespace Collision
