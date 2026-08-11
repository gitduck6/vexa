#pragma once
#include "defs.hpp"
#include "vec.hpp"
#include "math.hpp"
// forward declare cmath functions
NAMESPACE_BEGIN(monako)
inline NAMESPACE_BEGIN(shapes)


// returns sum of all sides
template<typename... Sides>
consteval inline fp32 Perimeter(const Sides... sides) {
    return (sides + ...);
}
// consteval version of shapes::Perimeter() for guaranteed compile-time execution
template<typename... Sides>
consteval inline fp32 PerimeterConsteval(const Sides... sides) {
    return (sides + ...);
}




template<class VectorType = Vec2f>
struct Triangle {
    using Vec = VectorType;
    Vec first;
    Vec middle;
    Vec last;

    // create a triangle: (pos1, pos2, pos3)
    explicit constexpr inline Triangle(Vec pos1, Vec pos2, Vec pos3) noexcept
        : first(pos1), middle(pos2), last(pos3) {}

    // create a triangle: (pos1, pos2, pos3)
    constexpr inline Triangle(Vec (&points)[3]) noexcept
        : first(points[0]), middle(points[1]), last(points[2]) {}

    fp32 area() {
        fp32 semi_p = PerimeterConsteval(first, middle, last) / 2;
        return ::sqrt(semi_p*(semi_p-first)*(semi_p-middle)*(semi_p-last));
    }
};




template<class Position = Vec2f, class Size = Vec2f>
struct Rect {
    Position pos;
    Size size;

    // create a rectangle: (x, y, w, h)
    explicit constexpr inline Rect(
        Position::Value x, Position::Value y, Size::Value width, Size::Value height
    ) noexcept: pos({x, y}), size(width, height) {}

    // create a rectangle: ({x, y}, {w, h})
    constexpr inline Rect(Position position, Size size) noexcept
        : pos(position), size(size) {}

    // create a square: ({x, y}, a)
    constexpr inline Rect(Position position, Size::Value side) noexcept
        : pos(position), size({side, side}) {}


    // methods: area(), perimeter(), center()
    constexpr inline Size::Value area()
    const noexcept { return size.x * size.y; }
    constexpr inline Size::Value perimeter()
    const noexcept { return 2*(size.x + size.y); }
    constexpr inline Position center()
    const noexcept { return {pos.x + size.x / 2, pos.y + size.y / 2}; }

    // methods: left(), right(), top(), bottom()
    constexpr inline Position left()
    const noexcept { return {pos.x, pos.y + size.y / 2}; }
    constexpr inline Position right()
    const noexcept { return {pos.x + size.x, pos.y + size.y / 2}; }
    constexpr inline Position top() 
    const noexcept { return {pos.x + size.x / 2, pos.y}; }
    constexpr inline Position bottom()
    const noexcept { return {pos.x + size.x / 2, pos.y + size.y}; }

    // methods: topLeft(), topRight(), bottomLeft(), bottomRight()
    constexpr inline Position topLeft()
    const noexcept { return pos; }
    constexpr inline Position topRight()
    const noexcept { return {pos.x + size.x, pos.y}; }
    constexpr inline Position bottomLeft()
    const noexcept { return {pos.x,pos.y + size.y}; }
    constexpr inline Position bottomRight()
    const noexcept { return {pos.x + size.x, pos.y + size.y}; }
};




constexpr uint32 CIRCLE_SEGMENTS = 1000;
template<const uint32 segments = CIRCLE_SEGMENTS, class Position = Vec2f, class Size = Vec2f>
struct Circle {
    Position pos;
    Size::Value radius;

    // create a circle: ({x, y}, r)
    explicit constexpr inline Circle(Position position, Size::Value radius) noexcept
        : pos(position), radius(radius) {}


    constexpr fp32 area() const noexcept {
        return math::PI32 * math::pow(radius, 2);
    }

    constexpr fp32 perimeter() const noexcept {
        return 2.f * math::PI32 * radius;
    }

    Circle& enlarge(const fp32 percent) noexcept {
        radius += radius * percent * 0.01f;
        return *this;
    }
};


NAMESPACE_END(shapes)
NAMESPACE_END(monako)
