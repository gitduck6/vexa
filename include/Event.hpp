#pragma once
#include "core/common.hpp"
NAMESPACE_BEGIN(cone)


class MK_NODISCARD Event
{
public: enum Type : uint64;

private:
    Type m_type;

public:
    Event() noexcept;

    static std::optional<Event> Poll() noexcept;


    Type type() const noexcept;
    //
    int key() const noexcept;
    // ..
    bool is_first() const noexcept;
    bool is_last() const noexcept;


private:
    // ..
    constexpr static inline uint64 M_ToSDL3EventTypeRuntime(Type type) noexcept;
    consteval static inline uint64 M_ToSDL3EventTypeCompt(Type type) noexcept;
    // ..
    constexpr static inline Type M_ToConeEventTypeRuntime(uint64 type) noexcept;
    consteval static inline Type M_ToConeEventTypeCompt(uint64 type) noexcept;
};


enum MK_NODISCARD Event::Type : uint64 {
    UNKNOWN = 0,
    FIRST = 1,
    LAST,
    QUIT,
    KEY_DOWN,
    KEY_UP,
};



NAMESPACE_END(cone)
