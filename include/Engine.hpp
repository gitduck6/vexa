#pragma once
#include "Window.hpp"
NAMESPACE_BEGIN(monako)

class Engine
{
    static inline bool _m_init = false;

    static inline Flags subsystems;
public:
    enum Subsystem { VIDEO, AUDIO, EVENT };

    static bool Init(Flags initial_subsystems) noexcept;
    static void Close() noexcept;

    static bool InitSubsystems(Flags subsystems) noexcept;
    static void CloseSubsystems(Flags subsystems) noexcept;
};


NAMESPACE_END(monako)
