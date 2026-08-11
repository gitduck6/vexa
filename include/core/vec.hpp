#pragma once
#include "defs.hpp"
#include <concepts>
NAMESPACE_BEGIN(monako)
inline NAMESPACE_BEGIN(vec)


template<class T>
concept VectorConcept = requires(T t) { t.x, t.y; };

template<VectorConcept VectorType>
static constexpr inline bool VecEqu(const VectorType& left, const VectorType& right) {
    return (left.x == right.x) && (left.y == right.y);
}

struct Vec2i {
    using Value = int32;
    Value x;
    Value y;
    constexpr Vec2i(Value x, Value y): x(x), y(y) {}
    constexpr bool operator== (Vec2i other) const noexcept { return VecEqu(*this, other); }
};

struct Vec2u {
    using Value = uint32;
    Value x;
    Value y;
    constexpr Vec2u(Value x, Value y): x(x), y(y) {}
};

struct Vec2f {
    using Value = fp32;
    Value x;
    Value y;
    constexpr Vec2f(Value x, Value y): x(x), y(y) {}
};


NAMESPACE_END(vec)
NAMESPACE_END(monako)
