#pragma once
#include "Renderer.hpp"
NAMESPACE_BEGIN(monako)

class [[nodiscard]] Window
{
    class Impl;
    Uptr<Impl> impl;


    class [[nodiscard]] M_Cfg
    {
        friend class Window;
    public:
        ConfigValue<Flags> flags;
    private:
        ConfigValue<const char*> title;
        ConfigValue<Vec2i> size;
        ConfigValue<Vec2i> position;
        //
        ConfigValue<bool> is_resizable;
        ConfigValue<bool> is_maximized;
        ConfigValue<bool> is_minimized;
        ConfigValue<bool> is_fullscreen;
        ConfigValue<bool> is_borderless;
        ConfigValue<bool> is_hidden;
        ConfigValue<bool> is_always_on_top;
        ConfigValue<bool> is_mouse_grabbed;
        ConfigValue<bool> is_mouse_relative;
        ConfigValue<bool> is_mouse_captured;
        ConfigValue<bool> is_keyboard_grabbed;

    public:
        constexpr M_Cfg() noexcept:
            flags(Flags{}),
            title(""),
            size(Vec2i{1280, 720}),
            position(Vec2i{0, 0}),
            is_resizable(false),
            is_maximized(false),
            is_minimized(false),
            is_fullscreen(false),
            is_borderless(false),
            is_hidden(false),
            is_always_on_top(false),
            is_mouse_grabbed(false),
            is_mouse_relative(false),
            is_mouse_captured(false),
            is_keyboard_grabbed(false)
        {}

        M_Cfg& reset() {
            size.value = size.defaultVal();
            return *this;
        }

        // M_Cfg& operator= (const M_Cfg& other) = default;
    }
    m_config;


public:
    using Cfg = M_Cfg;
    enum Trait : uint64;

    Window(Cfg config = Cfg{});
    ~Window();
    Window(Window&& other);
    Window& operator= (Window&& other);
    Window& operator= (const Window& copy_ctor) = delete;

    Window create();
    void destroy();
    bool exists();

    Flags defaultFlags() const noexcept;
    Flags& flags() noexcept;

    inline uint32 id() const noexcept;
    Renderer& renderer() noexcept;

    // RESIZABLE,
    // MINIMIZED,
    // MAXIMIZED,
    // FULLSCREEN,
    // BORDERLESS,
    // HIDDEN,
    // ALWAYS_ON_TOP,
    // INPUT_FOCUS,
    // MOUSE_GRABBED,
    // MOUSE_FOCUS,
    // MOUSE_CAPTURE,
    // MOUSE_RELATIVE,
    // KEYBOARD_GRABBED,


    Window& setRenderer(const Renderer::Cfg& recreatenderer_cfg);
    Window& setTitle(const char* title);
    Window& setSize(Vec2i size);
    Window& setPosition(Vec2i pos);

    Window& setResizable(bool yes = true);
    Window& setMaximized(bool yes = true);  Window& toggleMaximized();
    Window& setMinimized(bool yes = true);
    Window& setFullScreen(bool yes = true);
    Window& setBorderless(bool yes = true);
    Window& setHidden(bool yes = true);
    Window& setAlwaysOnTop(bool yes = true);
    Window& setMouseGrabbed(bool yes = true);
    Window& setMouseRelative(bool yes = true);
    Window& setMouseCapture(bool yes = true);
    Window& setKeyboardGrabbed(bool yes = true);

private:
    template<Trait> consteval static inline uint64 M_TranslateToSDL3WindowFlag();
    static inline uint64 M_TranslateToSDL3WindowFlagRuntime(uint64 traits);
};



enum Window::Trait : uint64 {
    DUMMY = 0,

    /* general */
    // RESIZABLE,
    // MINIMIZED,
    // MAXIMIZED,
    // FULLSCREEN,
    // BORDERLESS,
    // HIDDEN,
    TRANSPARENT,
    // ALWAYS_ON_TOP,
    UNFOCUSABLE,
    DENSE_PIXELS,

    /* input */
    // MOUSE_GRABBED,
    // MOUSE_RELATIVE,
    // KEYBOARD_GRABBED,
    // MOUSE_CAPTURE,
    //// INPUT_FOCUS,
    //// MOUSE_FOCUS,

    /* misc */
    // OCCLUDED,
    // MODAL,
    SKIP_TASKBAR,
    TOOLTIP_MENU,
    POPUP_MENU,
    // FILL_DOC,

    /* platform */
    OPENGL,
    VULKAN,
    METAL,
    EXTERN,
};


NAMESPACE_END(monako)
