#pragma once

struct Sphere;
struct AABB;
struct OBB;

namespace Collision {
bool IsCollision(const AABB& aabb1, const AABB& aabb2);
bool IsCollision(const AABB& aabb, const Sphere& sphere);
bool IsCollision(const OBB& obb, const Sphere& sphere);
} // namespace Collision
