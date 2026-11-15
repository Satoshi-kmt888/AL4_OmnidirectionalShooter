#include "Easing.h"

#include <cmath>
#include <numbers>

namespace {
constexpr float c1 = 1.70158f;
constexpr float c2 = c1 * 1.525f;
constexpr float c3 = c1 + 1.0f;
constexpr float c4 = (2.0f * std::numbers::pi_v<float>) / 3.0f;
constexpr float c5 = (2.0f * std::numbers::pi_v<float>) / 4.5f;

constexpr float n1 = 7.5625f;
constexpr float d1 = 2.75f;
} // namespace

namespace Easing {
float InSine(float t) { return 1.0f - std::cos((t * std::numbers::pi_v<float>)*0.5f); }
float OutSine(float t) { return std::sin((t * std::numbers::pi_v<float>)*0.5f); }
float InOutSine(float t) { return -(std::cos(t * std::numbers::pi_v<float>) - 1.0f) * 0.5f; }

float InQuad(float t) { return t * t; }
float OutQuad(float t) { return 1.0f - (1.0f - t) * (1.0f - t); }
float InOutQuad(float t) {
	float n = -2.0f * t + 2.0f;
	return t < 0.5f ? 2.0f * t * t : 1.0f - n * n * 0.5f;
}

float InCubic(float t) { return t * t * t; }
float OutCubic(float t) {
	float n = 1.0f - t;
	return 1.0f - n * n * n;
}
float InOutCubic(float t) {
	float n = -2.0f * t + 2.0f;
	return t < 0.5f ? 4.0f * t * t * t : 1.0f - (n * n * n) * 0.5f;
}

float InQuart(float t) { return t * t * t * t; }
float OutQuart(float t) {
	float n = 1.0f - t;
	return 1.0f - n * n * n * n;
}
float InOutQuart(float t) {
	float n = -2.0f * t + 2.0f;
	return t < 0.5f ? 8.0f * t * t * t * t : 1.0f - (n * n * n * n) * 0.5f;
}

float InQuint(float t) { return t * t * t * t * t; }
float OutQuint(float t) {
	float n = 1.0f - t;
	return 1.0f - n * n * n * n *n;
}
float InOutQuint(float t) {
	float n = -2.0f * t + 2.0f;
	return t < 0.5f ? 16.0f * t * t * t * t * t : 1.0f - (n * n * n * n * n) * 0.5f;
}

float InExpo(float t) {
	return t == 0.0f ? 0.0f : std::exp2f(10.0f * t - 10.0f);
}
float OutExpo(float t) {
	return t == 1.0f ? 1.0f : 1.0f - std::exp2f(-10.0f * t);
}
float InOutExpo(float t) {
	if (t == 0.0f) {
		return 0.0f;
	}else if (t == 1.0f) {
		return 1.0f;
	}else if (t < 0.5f) {
		return std::exp2f(20.0f * t - 10.0f) * 0.5f;
	}

	return (2.0f - std::exp2f(-20.0f * t + 10.0f)) * 0.5f;
}

float InCirc(float t) { return 1.0f - std::sqrt(1.0f - t * t); }
float OutCirc(float t) {
	float n = 1.0f - t;
	return std::sqrt(1.0f - n * n);
}
float InOutCirc(float t) {
	if (t < 0.5f) {
		float n = 2.0f * t;
		return (1.0f - std::sqrtf(1.0f - n * n)) * 0.5f;
	} else {
		float n = -2.0f * t + 2.0f;
		return (std::sqrtf(1.0f - n * n) + 1) * 0.5f;
	}
}

float InBack(float t) { return c3 * t * t * t - c1 * t * t; }
float OutBack(float t) {
	float n = t - 1.0f;
	return 1.0f + c3 * n * n * n + c1 * n * n;
}
float InOutBack(float t) {
	if (t < 0.5f) {
		float n = 2.0f * t;
		return (n * n * ((c2 + 1.0f) * 2.0f * t - c2)) * 0.5f;
	} else {
		float n = 2.0f * t - 2.0f;
		return (n * n * ((c2 + 1.0f) * (t * 2.0f - 2.0f) + c2) + 2.0f) * 0.5f;
	}
}

float InElastic(float t) {
	if (t == 0.0f) {
		return 0.0f;
	} else if (t == 1.0f) {
		return 1.0f;
	} else {
		return -std::exp2f(10.0f * t - 10.0f) * std::sin((t * 10.0f - 10.75f) * c4);
	}
}
float OutElastic(float t) {
	if (t == 0.0f) {
		return 0.0f;
	} else if (t == 1.0f) {
		return 1.0f;
	} else {
		return std::exp2f(-10.0f * t) * std::sin((t * 10.0f - 0.75f) * c4) + 1.0f;
	}
}
float InOutElastic(float t) {
	if (t == 0.0f) {
		return 0.0f;
	} else if (t == 1.0f) {
		return 1.0f;
	} else if (t < 0.5f) {
		return -(std::exp2f(20.0f * t - 10.0f) * std::sin((20.0f * t - 11.125f) * c5)) * 0.5f;
	} else {
		return (std::exp2f(-20.0f * t + 10.0f) * std::sin((20.0f * t - 11.125f) * c5)) * 0.5f + 1.0f;
	}
}

float InBounce(float t) { return 1.0f - OutBounce(1.0f - t); }
float OutBounce(float t) {
	if (t < 1.0f / d1) {
		return n1 * t * t;
	} else if (t < 2 / d1) {
		return n1 * (t -= 1.5f / d1) * t + 0.75f;
	} else if (t < 2.5f / d1) {
		return n1 * (t -= 2.25f / d1) * t + 0.9375f;
	} else {
		return n1 * (t -= 2.625f / d1) * t + 0.984375f;
	}
}
float InOutBounce(float t) {
	if (t < 0.5f) {
		return (1.0f - OutBounce(1.0f - 2.0f * t)) * 0.5f;
	} else {
		return (1.0f + OutBounce(2.0f * t - 1.0f)) * 0.5f;
	}
}
} // namespace Easing
