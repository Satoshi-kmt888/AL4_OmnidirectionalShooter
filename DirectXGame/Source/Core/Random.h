#pragma once

#include <random>
#include <type_traits>

namespace Random {
template<typename T> T Range(T min, T max) {
	static std::random_device device;
	static std::mt19937 generator(device());

	if constexpr (std::is_integral_v<T>) {
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(generator);
	} else {
		std::uniform_real_distribution<T> distribution(min, max);
		return distribution(generator);
	}
}
} // namespace Random
