#pragma once

struct Sphere;
struct AABB;
struct OBB;

namespace Collision {
bool IsCollision(const AABB& aabb1, const AABB& aabb2);
bool IsCollision(const AABB& aabb, const Sphere& sphere);
bool IsCollision(const OBB& obb, const Sphere& sphere);
bool IsCollision(const OBB& obb1, const OBB& obb2);
} // namespace Collision
