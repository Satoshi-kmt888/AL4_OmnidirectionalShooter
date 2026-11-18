#include "MathUtility.h"

#include <3d/WorldTransform.h>
#include <array>
#include <cassert>
#include <cmath>
#include <math/Matrix4x4.h>
#include <math/Vector3.h>
#include <numbers>

using namespace KamataEngine;

namespace {
/// <summary>
/// 作業用配列4x8を初期化する
/// </summary>
/// <param name="matrix"></param>
/// <returns></returns>
/// 左側4x4: 逆行列を求めたい行列
/// 右側4x4: 単位行列
std::array<std::array<float, 8>, 4> MakeWorkMatrix(const Matrix4x4& matrix) {
	std::array<std::array<float, 8>, 4> work{};
	for (int row = 0; row < 4; ++row) {
		for (size_t col = 0; col < 4; ++col) {
			work[row][col] = matrix.m[row][col];
			work[row][col + 4] = (row == col) ? 1.0f : 0.0f;
		}
	}

	return work;
}

/// <summary>
/// ピボット選択と入れ替えを行う
/// </summary>
/// <param name="work"></param>
/// <param name="index"></param>
/// <returns></returns>
bool PivotAndSwap(std::array<std::array<float, 8>, 4>& work, int index) {
	if (float pivot = work[index][index]; std::abs(pivot) >= 1e-8f) {
		return true;
	}

	int swap_row = -1;
	for (int row = 0; row < 4; ++row) {
		if (std::abs(work[row][index]) > 1e-8f) {
			swap_row = row;
			break;
		}
	}

	if (swap_row == -1) {
		return false; // 逆行列が存在しない
	}

	std::swap(work[index], work[swap_row]);
	return true;
}
} // namespace

namespace MathUtility {
float ConvertToRadian(float degree) {
	constexpr float k_degree_to_radian = std::numbers::pi_v<float> / 180.0f;
	return degree * k_degree_to_radian;
}

float ConvertToDegree(float radian) {
	constexpr float k_radian_to_degree = 180.0f / std::numbers::pi_v<float>;
	return radian * k_radian_to_degree;
}

Vector3 operator+(const Vector3& v) { return Vector3{+v.x, +v.y, +v.z}; }
Vector3 operator-(const Vector3& v) { return Vector3{-v.x, -v.y, -v.z}; }

Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Vector3{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z}; }

Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Vector3{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z}; }

Vector3 operator*(const Vector3& v, float scalar) { return Vector3{v.x * scalar, v.y * scalar, v.z * scalar}; }

Vector3 operator*(float scalar, const Vector3& v) { return v * scalar; }

Vector3 operator/(const Vector3& v, float scalar) { return Vector3{v.x / scalar, v.y / scalar, v.z / scalar}; }

Vector3& operator+=(Vector3& v1, const Vector3& v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return v1;
}

Vector3& operator-=(Vector3& v1, const Vector3& v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}

Vector3& operator*=(Vector3& v, float scalar) {
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	return v;
}

Vector3& operator/=(Vector3& v, float scalar) {
	v.x /= scalar;
	v.y /= scalar;
	v.z /= scalar;
	return v;
}

float Length(const Vector3& v) { return std::sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); }

Vector3 Normalize(const Vector3& v) {
	if (float lengthSquared = (v.x * v.x) + (v.y * v.y) + (v.z * v.z); lengthSquared > 0.0f) {
		float inverseLength = 1.0f / std::sqrtf(lengthSquared);
		return {v.x * inverseLength, v.y * inverseLength, v.z * inverseLength};
	}

	return {0.0f, 0.0f, 0.0f};
}

float Dot(const Vector3& v1, const Vector3& v2) { return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z); }

Vector3 Cross(const Vector3& v1, const Vector3& v2) { return Vector3{(v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x)}; }

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) noexcept {
	Matrix4x4 result{};

	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			result.m[row][column] = m1.m[row][0] * m2.m[0][column] + m1.m[row][1] * m2.m[1][column] + m1.m[row][2] * m2.m[2][column] + m1.m[row][3] * m2.m[3][column];
		}
	}

	return result;
}

Matrix4x4 MakeIdentityMatrix() {
	Matrix4x4 result{};

	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	return result;
}

KamataEngine::Matrix4x4 InverseMatrix(const Matrix4x4& matrix) {
	// 求める行列+単位行列の4x8行列を作成
	auto work = MakeWorkMatrix(matrix);

	// ガウスジョルダン法による掃き出し
	for (int i = 0; i < 4; ++i) {
		if (!PivotAndSwap(work, i)) {
			return MakeIdentityMatrix();
		}

		float inv_pivot = 1.0f / work[i][i];

		// 注目している行全体をピボットで割る
		for (int col = 0; col < 8; ++col) {
			work[i][col] *= inv_pivot;
		}

		// 他の行の該当列を0にする
		for (int row = 0; row < 4; ++row) {
			if (row == i) {
				continue;
			}

			float factor = work[row][i];
			for (int col = 0; col < 8; ++col) {
				work[row][col] -= factor * work[i][col];
			}
		}
	}

	// 計算した行列のうち、行列の右側部分が逆行列なので結果に格納する
	Matrix4x4 result{};
	for (int row = 0; row < 4; ++row) {
		for (size_t col = 0; col < 4; ++col) {
			result.m[row][col] = work[row][col + 4];
		}
	}

	return result;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) noexcept {
	Matrix4x4 result = MakeIdentityMatrix();

	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;

	return result;
}

Matrix4x4 MakeRotateXMatrix(float radian) noexcept {
	Matrix4x4 result = MakeIdentityMatrix();

	result.m[1][1] = std::cosf(radian);
	result.m[1][2] = std::sinf(radian);
	result.m[2][1] = -std::sinf(radian);
	result.m[2][2] = std::cosf(radian);

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) noexcept {
	Matrix4x4 result = MakeIdentityMatrix();

	result.m[0][0] = std::cosf(radian);
	result.m[0][2] = -std::sinf(radian);
	result.m[2][0] = std::sinf(radian);
	result.m[2][2] = std::cosf(radian);

	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) noexcept {
	Matrix4x4 result = MakeIdentityMatrix();

	result.m[0][0] = std::cosf(radian);
	result.m[0][1] = std::sinf(radian);
	result.m[1][0] = -std::sinf(radian);
	result.m[1][1] = std::cosf(radian);

	return result;
}

Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotation) noexcept { return MakeRotateXMatrix(rotation.x) * MakeRotateYMatrix(rotation.y) * MakeRotateZMatrix(rotation.z); }

Matrix4x4 MakeTranslateMatrix(const Vector3& translation) noexcept {
	Matrix4x4 result = MakeIdentityMatrix();

	result.m[3][0] = translation.x;
	result.m[3][1] = translation.y;
	result.m[3][2] = translation.z;

	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotation, const Vector3& translation) noexcept {
	return MakeScaleMatrix(scale) * MakeRotateXYZMatrix(rotation) * MakeTranslateMatrix(translation);
}

void UpdateWorldTransform(WorldTransform& world_transform) {
	// SRTを合成してアフィン変換行列を計算する
	world_transform.matWorld_ = MakeAffineMatrix(world_transform.scale_, world_transform.rotation_, world_transform.translation_);

	if (world_transform.parent_) {
		world_transform.matWorld_ = world_transform.matWorld_ * world_transform.parent_->matWorld_;
	}

	// 定数バッファへの書き込み
	world_transform.TransferMatrix();
}
Vector3 Transform(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{};

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + 1.0f * m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + 1.0f * m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + 1.0f * m.m[3][2];
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + 1.0f * m.m[3][3];

	assert(w != 0.0f);

	return result /= w;
}
} // namespace MathUtility
