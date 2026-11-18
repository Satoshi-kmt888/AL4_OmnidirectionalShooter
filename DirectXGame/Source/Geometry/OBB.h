#pragma once

#include <array>
#include <math/Vector3.h>

/// <summary>
/// OBB
/// </summary>
struct OBB {
	KamataEngine::Vector3 center;
	std::array<KamataEngine::Vector3, 3> orientations;
	KamataEngine::Vector3 size;
};
