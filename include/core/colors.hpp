#pragma once
#include <concepts>
#include "defs.hpp"
NAMESPACE_BEGIN(monako)
inline NAMESPACE_BEGIN(colors)


template <typename T>
requires (std::same_as<uint8, T> || std::same_as<fp32, T>)
struct ColorBase {
    T r, g, b;
    T a = 255;

    // increase r, g and b values by @arg n
    T& increase(T n) {
        r += n; g += n; b += n;
        return *this;
    }

    // decrease r, g and b values by @arg n
    T& decrease(T n) {
        r -= n; g -= n; b -= n;
        return *this;
    }
};


struct ColorU8  : ColorBase<uint8> {
    using This = ColorU8;
    using Value = uint8;

    constexpr ColorU8 (Value r, Value g, Value b, Value a=255) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    };

    static const This BLACK;
    static const This WHITE;
    static const This GREY;
    //
    static const This RED;
    static const This GREEN;
    static const This BLUE;
    //
    static const This YELLOW;
    static const This CYAN;
    static const This MAGENTA;
};


struct ColorF32  : ColorBase<fp32> {
    using This = ColorF32;
    using Value = fp32;

    constexpr ColorF32 (Value r, Value g, Value b, Value a=255) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    };

    static const This BLACK;
    static const This WHITE;
    static const This GREY;
    //
    static const This RED;
    static const This GREEN;
    static const This BLUE;
    //
    static const This YELLOW;
    static const This CYAN;
    static const This MAGENTA;
};

template<class T>
concept ColorConcept = (
    is_same_t<ColorU8, T> || is_same_t<ColorF32, T>
);

constexpr inline const ColorU8 ColorU8::BLACK = {0, 0, 0};
constexpr inline const ColorU8 ColorU8::WHITE = {255, 255, 255};
constexpr inline const ColorU8 ColorU8::GREY = {128, 128, 128};
constexpr inline const ColorU8 ColorU8::RED = {255, 0, 0};
constexpr inline const ColorU8 ColorU8::GREEN = {0, 255, 0};
constexpr inline const ColorU8 ColorU8::BLUE = {0, 0, 255};
constexpr inline const ColorU8 ColorU8::YELLOW = {255, 255, 0};
constexpr inline const ColorU8 ColorU8::CYAN = {0, 255, 255};
constexpr inline const ColorU8 ColorU8::MAGENTA = {255, 0, 255};

constexpr inline const ColorF32 ColorF32::BLACK = {0.f, 0.f, 0.f};
constexpr inline const ColorF32 ColorF32::WHITE = {255.f, 255.f, 255.f};
constexpr inline const ColorF32 ColorF32::GREY = {127.5f, 127.5f, 127.5f};
constexpr inline const ColorF32 ColorF32::RED = {255.f, 0.f, 0.f};
constexpr inline const ColorF32 ColorF32::GREEN = {0.f, 255.f, 0.f};
constexpr inline const ColorF32 ColorF32::BLUE = {0.f, 0.f, 255.f};
constexpr inline const ColorF32 ColorF32::YELLOW = {255.f, 255.f, 0.f};
constexpr inline const ColorF32 ColorF32::CYAN = {0.f, 255.f, 255.f};
constexpr inline const ColorF32 ColorF32::MAGENTA = {255.f, 0.f, 255.f};

NAMESPACE_END(colors)
NAMESPACE_END(monako)
