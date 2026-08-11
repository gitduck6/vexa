#pragma once
#include "defs.hpp"
#include "math.hpp"
NAMESPACE_BEGIN(monako)

struct Angle {
    fp32 radians;

    constexpr Angle (fp32 radians): radians(radians) {}
    constexpr Angle (fp32 degrees, void*): radians(degrees) {}

    // returns angle value in degrees
    constexpr fp32 degrees() const noexcept {
        return math::toDegrees(radians);
    }

    constexpr fp32 clamp() noexcept {
        return math::clamp(radians, 0.f, 360.f);
    }

    constexpr fp32 normalize() const noexcept {
        return Angle{radians}.clamp() * (1.f/math::PI32);
    }
};


NAMESPACE_END(monako)
