#pragma once

namespace KamataEngine {
struct Vector3;
struct Matrix4x4;
class WorldTransform;
} // namespace KamataEngine

namespace MathUtility {
float ConvertToRadian(float degree);
float ConvertToDegree(float radian);

// ベクトル 単項演算子のオーバーロード
KamataEngine::Vector3 operator+(const KamataEngine::Vector3& v);
KamataEngine::Vector3 operator-(const KamataEngine::Vector3& v);

// ベクトル 二項演算子のオーバーロード
KamataEngine::Vector3 operator+(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);
KamataEngine::Vector3 operator-(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);
KamataEngine::Vector3 operator*(const KamataEngine::Vector3& v, float scalar);
KamataEngine::Vector3 operator*(float scalar, const KamataEngine::Vector3& v);
KamataEngine::Vector3 operator/(const KamataEngine::Vector3& v, float scalar);

// ベクトル 複合代入演算子のオーバーロード
KamataEngine::Vector3& operator+=(KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);
KamataEngine::Vector3& operator-=(KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);
KamataEngine::Vector3& operator*=(KamataEngine::Vector3& v, float scalar);
KamataEngine::Vector3& operator/=(KamataEngine::Vector3& v, float scalar);

// ベクトルの長さを求める
float Length(const KamataEngine::Vector3& v);

// 正規化
KamataEngine::Vector3 Normalize(const KamataEngine::Vector3& v);

// 内積
float Dot(const KamataEngine::Vector3& v);
// 外積
KamataEngine::Vector3 Cross(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

// 行列 二項演算子のオーバーロード
KamataEngine::Matrix4x4 operator*(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2) noexcept;

// 単位行列を求める
KamataEngine::Matrix4x4 MakeIdentityMatrix();

// 拡縮行列を求める
KamataEngine::Matrix4x4 MakeScaleMatrix(const KamataEngine::Vector3& scale) noexcept;

// 回転行列を求める
KamataEngine::Matrix4x4 MakeRotateXMatrix(float radian) noexcept;
KamataEngine::Matrix4x4 MakeRotateYMatrix(float radian) noexcept;
KamataEngine::Matrix4x4 MakeRotateZMatrix(float radian) noexcept;
KamataEngine::Matrix4x4 MakeRotateXYZMatrix(const KamataEngine::Vector3& rotation) noexcept;

// 平行移動行列を求める
KamataEngine::Matrix4x4 MakeTranslateMatrix(const KamataEngine::Vector3& translation) noexcept;

// アフィン変換行列を求める
KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotation, const KamataEngine::Vector3& translation) noexcept;

// トランスフォームを更新する
void WorldTransformUpdate(KamataEngine::WorldTransform& world_transform);
} // namespace MathUtility
