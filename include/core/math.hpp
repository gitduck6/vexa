#pragma once
#include "defs.hpp"
#include <cmath>
NAMESPACE_BEGIN(cone)
NAMESPACE_BEGIN(math)

// compile time PI as fp32 and fp64
constexpr fp32 PI32 = 3.14159265f;
constexpr fp64 PI64 = 3.14159265358979323846;
// to make (x / PI32) and (x / PI64) optimizable, where x is a runtime value
constexpr fp32 PI32_INV = 1.0f/3.14159265f;
constexpr fp64 PI64_INV = 1.0f/3.14159265358979323846;


// sqrt for fp32
template <const fp32 x>
consteval inline auto sqrt_fp32() -> decltype(x) {
    return std::sqrtf(x);
}
// sqrt for fp64
template <const fp64 x>
consteval inline auto sqrt_fp64() -> decltype(x) {
    return std::sqrt(x);
}


// sqrt for fp32
template <const fp32 x, const fp32 exp>
consteval inline auto pow() -> decltype(x) {
    return std::powf(x, exp);
}
// pow for fp64
template <const fp64 x, const fp32 exp>
consteval inline auto pow() -> decltype(x) {
    return std::pow(x, exp);
}



// convert radians to degrees
constexpr fp32 toDegrees(fp32 radians) noexcept {
    return radians * 180.f * PI32_INV;
}
// convert degrees to radians
constexpr fp32 toRadians(fp32 degrees) noexcept {
    return degrees * (PI32 / 180.f);
}



// return clamped value of @arg value between @arg min and @arg max
template<class V>
constexpr V clamp(V value, V min, V max) {
    if (max < value) return max;
    else if (min > value) return min;
    return value;
}
// overload math::clamp for the case that 
template<class V, class T, class U>
constexpr auto clamp(V value, T min, U max) -> std::common_type_t<V, T, U> {
    if (max < value) return max;
    else if (min > value) return min;
    return value;
}


NAMESPACE_END(math)
NAMESPACE_END(cone)
