#include "alt/SDL3.hpp"
#include "Engine.hpp"
NAMESPACE_BEGIN(monako)

bool Engine::Init(const Flags initial_subsystems) noexcept {
    if (!_m_init) {
        _m_init = true;
        return InitSubsystems(initial_subsystems);
    }
    return false;
}

void Engine::Close() noexcept {
    subsystems.reset().value();
    _m_init = false;
    SDL_Quit();
}

bool Engine::InitSubsystems(Flags subsystems) noexcept {
    subsystems.add(subsystems);
    return SDL_InitSubSystem(subsystems.value());
}

void Engine::CloseSubsystems(Flags subsystems) noexcept {
    subsystems.sub(subsystems);
    SDL_QuitSubSystem(subsystems.value());
}


bool Engine::CaptureMouse(bool yes) noexcept {
    return SDL_CaptureMouse(yes);
}

bool Engine::IsMouseCaptured() noexcept {
    return (SDL_GetWindowFlags(nullptr) & SDL_WINDOW_MOUSE_CAPTURE);
}


NAMESPACE_END(monako)
