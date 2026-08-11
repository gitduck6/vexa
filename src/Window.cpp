#include "alt/SDL3.hpp"
#include "../include/Window.hpp"
NAMESPACE_BEGIN(monako)

#define FN "Window::{}(): "

#define DEF_MSG static constexpr inline const char* const
    DEF_MSG mf_failed_to_create_window
        { "an error occured while creating the renderer" };

    DEF_MSG mf_window_never_existed_before
        { "invalid call on a window that has never been created" };

    DEF_MSG mf_window_currently_doesnt_exist
        { "invalid call on an already destroyed window" };

    DEF_MSG me_window_already_exists
        { "renderer already exists" };

    DEF_MSG mf_renderer_doesnt_exist
        { "window doesn't have a renderer" };

#undef DEF_MSG



using This = Window;


NAMESPACE_BEGIN()
using enum Window::Trait;

struct TraitMap {
    Window::Trait trait;
    uint64 flag;
};

constexpr TraitMap mappings[] = {
    // { RESIZABLE,     SDL_WINDOW_RESIZABLE },
    // { MINIMIZED,     SDL_WINDOW_MINIMIZED },
    // { MAXIMIZED,     SDL_WINDOW_MAXIMIZED },
    // { FULLSCREEN,    SDL_WINDOW_FULLSCREEN },
    // { BORDERLESS,    SDL_WINDOW_BORDERLESS },
    // { HIDDEN,        SDL_WINDOW_HIDDEN },
    { TRANSPARENT,   SDL_WINDOW_TRANSPARENT },
    // { ALWAYS_ON_TOP, SDL_WINDOW_ALWAYS_ON_TOP },
    { UNFOCUSABLE,   SDL_WINDOW_NOT_FOCUSABLE },
    { DENSE_PIXELS,  SDL_WINDOW_HIGH_PIXEL_DENSITY },
    // { INPUT_FOCUS,      SDL_WINDOW_INPUT_FOCUS },
    // { MOUSE_GRABBED,    SDL_WINDOW_MOUSE_GRABBED },
    // { MOUSE_FOCUS,      SDL_WINDOW_MOUSE_FOCUS },
    // { MOUSE_CAPTURE,    SDL_WINDOW_MOUSE_CAPTURE },
    // { MOUSE_RELATIVE,   SDL_WINDOW_MOUSE_RELATIVE_MODE },
    // { KEYBOARD_GRABBED, SDL_WINDOW_KEYBOARD_GRABBED },
    // { OCCLUDED,     SDL_WINDOW_OCCLUDED },
    // { MODAL,        SDL_WINDOW_MODAL },
    { SKIP_TASKBAR, SDL_WINDOW_UTILITY },
    { TOOLTIP_MENU, SDL_WINDOW_TOOLTIP },
    { POPUP_MENU,   SDL_WINDOW_POPUP_MENU },
    // { FILL_DOC,     SDL_WINDOW_FILL_DOCUMENT },
    { OPENGL, SDL_WINDOW_OPENGL },
    { VULKAN, SDL_WINDOW_VULKAN },
    { METAL,  SDL_WINDOW_METAL },
    { EXTERN, SDL_WINDOW_EXTERNAL },
};

NAMESPACE_END()

template<This::Trait traits>
consteval static inline uint64 M_TranslateToSDL3WindowFlag() {
    uint64 sdl_flags = 0;
    for (const auto& m : mappings) {
        if (traits & m.trait) sdl_flags |= m.flag;
    }
    return sdl_flags;
}

uint64 This::M_TranslateToSDL3WindowFlagRuntime(uint64 traits) {
    uint64 sdl_flags = 0;
    for (const auto& m : mappings) {
        if (traits & static_cast<uint64>(m.trait)) sdl_flags |= m.flag;
    }
    return sdl_flags;
}






class This::Impl {
    SDL_Window* m_window = nullptr;
    uint32 m_id = 0;
public:
    bool window_ever_existed = false;
    bool window_exists = false;
    Renderer renderer = Renderer{};
    bool renderer_set = false;

    explicit Impl() = default;

    ~Impl() {
        if (window_exists) {
            SDL_DestroyWindow(m_window);
            window_exists = false;
        }
    }

    SDL_Window* ptr() { return m_window; }

    SDL_Window* createWindow(Cfg config) {
        if (!window_exists)
        {
            m_window = SDL_CreateWindow(
                config.title.value, config.size.value.x, config.size.value.y,
                This::M_TranslateToSDL3WindowFlagRuntime(config.flags.value.value())
            );
            IF_THEN(!m_window,   log::fatal(FN"{}", __func__, mf_failed_to_create_window);)

            m_id = SDL_GetWindowID(m_window);
            window_ever_existed = window_exists = true;
        }
        else { log::error(FN"{}", __func__, me_window_already_exists); }

        return m_window;
    }
};

This::Window(Cfg config): impl(new Impl{}), m_config(config) {}
This::~Window() { impl = nullptr; }

This::Window(Window&& other) {
    impl = std::move(other.impl);
    m_config = other.m_config;
}

Window& This::operator= (Window&& other) {
    impl = std::move(other.impl);
    m_config = other.m_config;
    return *this;
}



#define TRY_WINDOW_SET_POS(_win, _x, _y) \
    if (!SDL_SetWindowPosition(_win, _x, _y)) \
        log::error("Failed to set position of window at [{}]. Hence, do you use wayland?", (void*)_win);


// if (!SDL_SetWindowPosition(impl->ptr(), pos.x, pos.y), log::error("Setting window position failed. Hence, do you use wayland?"););
#define IS_CFG_DEFAULT(_cfg_prop)  (m_config._cfg_prop.value == m_config._cfg_prop.defaultVal())

Window This::create() {
    Window build = {};
    build.m_config = m_config;

    auto* new_window = build.impl->createWindow(build.m_config);
    IF_THEN (!new_window,   log::fatal(FN"{}", __func__, mf_window_currently_doesnt_exist);)
    log::info(FN"created new window at [{}]", __func__, (void*)new_window);

    if (!IS_CFG_DEFAULT(title))    SDL_SetWindowTitle(new_window, m_config.title);
    if (!IS_CFG_DEFAULT(size))    SDL_SetWindowSize(new_window, m_config.size.value.x, m_config.size.value.y);
    if (!IS_CFG_DEFAULT(position))    TRY_WINDOW_SET_POS(new_window, m_config.position.value.x, m_config.position.value.y)
    if (!IS_CFG_DEFAULT(is_resizable))    SDL_SetWindowResizable(new_window, m_config.is_resizable);
    if (!IS_CFG_DEFAULT(is_minimized))  if(m_config.is_minimized) SDL_MinimizeWindow(new_window);
    if (!IS_CFG_DEFAULT(is_maximized))  if(m_config.is_maximized) SDL_MaximizeWindow(new_window);
    if (!IS_CFG_DEFAULT(is_fullscreen))    SDL_SetWindowFullscreen(new_window, m_config.is_fullscreen);
    if (!IS_CFG_DEFAULT(is_borderless))    SDL_SetWindowBordered(new_window, m_config.is_borderless);
    if (!IS_CFG_DEFAULT(is_hidden))  if(m_config.is_hidden) SDL_HideWindow(new_window);
    if (!IS_CFG_DEFAULT(is_always_on_top))    SDL_SetWindowAlwaysOnTop(new_window, m_config.is_always_on_top);
    if (!IS_CFG_DEFAULT(is_mouse_grabbed))    SDL_SetWindowMouseGrab(new_window, m_config.is_mouse_grabbed);
    if (!IS_CFG_DEFAULT(is_mouse_relative))    SDL_SetWindowRelativeMouseMode(new_window, m_config.is_mouse_relative);
    if (!IS_CFG_DEFAULT(is_mouse_captured))  if(m_config.is_mouse_captured) SDL_CaptureMouse(new_window);
    if (!IS_CFG_DEFAULT(is_keyboard_grabbed))    SDL_SetWindowKeyboardGrab(new_window, m_config.is_keyboard_grabbed);

    if (impl->renderer_set) build.impl->renderer = build.impl->renderer.create((SDL_Window*)new_window);
    return build;
}


void This::destroy() {
    impl = nullptr;
    m_config.reset();
}


bool This::exists() {
    return impl->window_exists;
}


Flags This::defaultFlags() const noexcept {
    return m_config.flags.defaultVal();
}

Flags& This::flags() noexcept {
    return m_config.flags.value;
}

inline uint32 This::id() const noexcept {
    return SDL_GetWindowID(impl->ptr());
}

Renderer& This::renderer() noexcept {
    IF_THEN(!impl,   log::info(FN"{} impl->nullptr!", __func__, mf_window_never_existed_before););
    IF_THEN(!impl->window_ever_existed,   log::fatal(FN"{}", __func__, mf_window_never_existed_before);)
    IF_THEN(!impl->window_exists,   log::fatal(FN"{}", __func__, mf_window_never_existed_before);)
    IF_THEN(!impl->renderer.exists(),   log::error(FN": {}", __func__, mf_renderer_doesnt_exist);)
    return impl->renderer;
}

// assign internal (un)initialized renderer's configuration
Window& This::setRenderer(const Renderer::Cfg& renderer_cfg) {
    impl->renderer_set = true;
    impl->renderer.m_config = renderer_cfg;
    if (impl && impl->window_exists) { impl->renderer = impl->renderer.create(impl->ptr()); }
    return *this;
}

Window& This::setTitle(const char* title) {
    m_config.title.value = title;
    if (impl && impl->window_exists) { SDL_SetWindowTitle(impl->ptr(), title); }
    return *this;
}

Window& This::setSize(Vec2i size) {
    m_config.size.value = size;
    if (impl && impl->window_exists) { SDL_SetWindowSize(impl->ptr(), size.x, size.y); }
    return *this;
}

Window& This::setPosition(Vec2i pos) {
    m_config.position.value = pos;
    if (impl && impl->window_exists) {
        TRY_WINDOW_SET_POS(impl->ptr(), m_config.position.value.x, m_config.position.value.y);
    }
    return *this;
}


Window& This::setResizable(bool yes) {
    m_config.is_resizable = yes;
    if (impl && impl->window_exists) { SDL_SetWindowResizable(impl->ptr(), yes); }
    return *this;
}

Window& This::setMaximized(bool yes) {
    m_config.is_maximized = yes;
    if (impl && impl->window_exists) {
        if(yes) { SDL_MaximizeWindow(impl->ptr()); }
        else { SDL_RestoreWindow(impl->ptr()); }
    }
    return *this;
}
// friend of setMaximized
Window& This::toggleMaximized() {
    this->setMaximized(!m_config.is_maximized);
    return *this;
}

Window& This::setMinimized(bool yes) {
    m_config.is_minimized = yes;
    if (impl && impl->window_exists) { SDL_MinimizeWindow(impl->ptr()); }
    return *this;
}

Window& This::setFullScreen(bool yes) {
    m_config.is_fullscreen = yes;
    if (impl && impl->window_exists) { SDL_SetWindowFullscreen(impl->ptr(), yes); }
    return *this;
}

Window& This::setBorderless(bool yes) {
    m_config.is_borderless = yes;
    if (impl && impl->window_exists) { SDL_SetWindowBordered(impl->ptr(), yes); }
    return *this;
}

Window& This::setHidden(bool yes) {
    m_config.is_hidden = yes;
    if (impl && impl->window_exists) { SDL_HideWindow(impl->ptr()); }
    return *this;
}

Window& This::setAlwaysOnTop(bool yes) {
    m_config.is_always_on_top = yes;
    if (impl && impl->window_exists) { SDL_SetWindowAlwaysOnTop(impl->ptr(), yes); }
    return *this;
}

Window& This::setKeyboardGrabbed(bool yes) {
    m_config.is_keyboard_grabbed = yes;
    if (impl && impl->window_exists) { SDL_SetWindowKeyboardGrab(impl->ptr(), yes); }
    return *this;
}

Window& This::setMouseGrabbed(bool yes) {
    m_config.is_mouse_grabbed = yes;
    if (impl && impl->window_exists) { SDL_SetWindowMouseGrab(impl->ptr(), yes); }
    return *this;
}

Window& This::setMouseRelative(bool yes) {
    m_config.is_mouse_relative = yes;
    if (impl && impl->window_exists) { SDL_SetWindowRelativeMouseMode(impl->ptr(), yes); }
    return *this;
}

Window& This::setMouseCapture(bool yes) {
    m_config.is_mouse_captured = yes;
    if (impl && impl->window_exists) { SDL_CaptureMouse(impl->ptr()); }
    return *this;
}


NAMESPACE_END(monako)
