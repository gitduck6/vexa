#include "alt/SDL3.hpp"
#include "Event.hpp"
NAMESPACE_BEGIN(monako)

using This = Event;


struct TypeMap {
    This::Type type;
    uint64 sdl_type;
};


static constexpr TypeMap type_maps[] = {
    { This::FIRST, SDL_EVENT_FIRST },
    { This::LAST, SDL_EVENT_LAST },
    { This::QUIT, SDL_EVENT_QUIT },
    { This::KEY_DOWN, SDL_EVENT_KEY_DOWN },
    { This::KEY_UP, SDL_EVENT_KEY_UP },
};


constexpr inline uint64 This::M_ToSDL3EventTypeRuntime(This::Type type) noexcept
{
    for(const auto& [mk_type, sdl_type] : type_maps)  if(mk_type == type)  return sdl_type;
    return -1;  // intentional
}
consteval inline uint64 This::M_ToSDL3EventTypeCompt(This::Type type) noexcept
{
    return M_ToSDL3EventTypeRuntime(type);
}

constexpr inline This::Type This::M_ToMonakoEventTypeRuntime(uint64 sdl_type) noexcept
{
    for(const auto& [mk_type, _sdl_type] : type_maps)  if(_sdl_type == sdl_type)  return mk_type;
    return This::UNKNOWN;
}
consteval inline This::Type This::M_ToMonakoEventTypeCompt(uint64 type) noexcept
{
    return M_ToMonakoEventTypeRuntime(type);
}



This::Event() noexcept = default;


std::optional<Event> This::Poll() noexcept {
    SDL_Event event;
    IF_THEN(!SDL_PollEvent(&event),   return std::nullopt;);

    Event build;
    build.m_type = M_ToMonakoEventTypeRuntime(event.type);

    return build;
}



This::Type This::type() const noexcept {
    return m_type;
}


bool This::is_first() const noexcept {
    return m_type == Type::FIRST;
}

bool This::is_last() const noexcept {
    return m_type == Type::LAST;
}


NAMESPACE_END(monako)
