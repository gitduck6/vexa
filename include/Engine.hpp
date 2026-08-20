#pragma once
#include "Window.hpp"
NAMESPACE_BEGIN(monako)

class Engine
{
    static inline bool m_init = false;
    static inline Flags m_subsystems;

public:
    enum Subsystem { VIDEO, AUDIO, EVENT };

    static bool Init(Flags initial_subsystems) noexcept;
    static void Close() noexcept;
    static bool InitSubsystems(Flags subsystems) noexcept;
    static void CloseSubsystems(Flags subsystems) noexcept;

    static bool setMouseCaptured(bool yes) noexcept;
    static bool IsMouseCaptured() noexcept;
};



NAMESPACE_END(monako)
