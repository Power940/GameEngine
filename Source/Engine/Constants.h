#pragma once

#include <numbers>

namespace STR_FALL
{
	static const double PI = std::numbers::pi;
	static const float F_PI = static_cast<float>(std::numbers::pi);

	static const double PI2 = std::numbers::pi * 2.0;
	static const float F_PI2 = static_cast<float>(std::numbers::pi) * 2.0f;

	static const double HPI = std::numbers::pi / 2.0;
	static const float F_HPI = static_cast<float>(std::numbers::pi) / 2.0f;

	static const double RAD_DEG = std::numbers::pi / 180.0;
	static const float F_RAD_DEG = static_cast<float>(std::numbers::pi) / 180.0f;

	static const double DEG_RAD = 180.0 / std::numbers::pi;
	static const float F_DEG_RAD = 180.0f / static_cast<float>(std::numbers::pi);
}