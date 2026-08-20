#pragma once
#include "Renderer.hpp"
NAMESPACE_BEGIN(cone)

class MK_NODISCARD Window
{
    class Impl;
    Uptr<Impl> impl;


    class MK_NODISCARD M_Cfg
    {
        friend class Window;
    public:
        ConfigValue<Flags> flags;
    // private:
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
        ConfigValue<bool> is_keyboard_grabbed;

    public:
        constexpr M_Cfg() noexcept:
            flags(Flags{}),
            title(""),
            size(Vec2i{0, 0}),
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
            is_keyboard_grabbed(false)
        {}

        M_Cfg& reset() {
            flags = flags.defaultVal();
            title = title.defaultVal();
            size = size.defaultVal();
            position = position.defaultVal();
            is_resizable = is_resizable.defaultVal();
            is_maximized = is_maximized.defaultVal();
            is_minimized = is_minimized.defaultVal();
            is_fullscreen = is_fullscreen.defaultVal();
            is_borderless = is_borderless.defaultVal();
            is_hidden = is_hidden.defaultVal();
            is_always_on_top = is_always_on_top.defaultVal();
            is_mouse_grabbed = is_mouse_grabbed.defaultVal();
            is_mouse_relative = is_mouse_relative.defaultVal();
            is_keyboard_grabbed = is_keyboard_grabbed.defaultVal();
            return *this;
        }
    }
    m_build_config;


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
    inline uint32 id() const noexcept;

    /** under construction **/
    // Flags defaultFlags() const noexcept;
    // Flags& flags() noexcept;

    using M_WindowPtr = void*;
    using M_WindowFlags = uint64;
    static inline M_WindowFlags _getActiveFlags(M_WindowPtr win);
    static inline void _trySetTitle(M_WindowPtr win, const char* title);
    static inline void _trySetSize(M_WindowPtr win, int x, int y);
    static inline void _trySetPos(M_WindowPtr win, int x, int y);
    static inline void _trySetResizable(M_WindowPtr win, bool yes);
    static inline void _trySetMinimized(M_WindowPtr win, bool yes);
    static inline void _trySetMaximized(M_WindowPtr win, bool yes);
    static inline void _trySetFullscreen(M_WindowPtr win, bool yes);
    static inline void _trySetBorderless(M_WindowPtr win, bool yes);
    static inline void _trySetHidden(M_WindowPtr win, bool yes);
    static inline void _trySetAlwaysOnTop(M_WindowPtr win, bool yes);
    static inline void _trySetMouseGrabbed(M_WindowPtr win, bool yes);
    static inline void _trySetMouseRelative(M_WindowPtr win, bool yes);
    static inline void _trySetKeyboardGrabbed(M_WindowPtr win, bool yes);

    Renderer& renderer() noexcept;
    const char* title();
    Vec2i size();
    Vec2i position();
    bool isResizable();
    bool isMaximized();
    bool isMinimized();
    bool isFullScreen();
    bool isBorderless();
    bool isHidden();
    bool isAlwaysOnTop();
    bool isKeyboardGrabbed();
    bool isMouseGrabbed();
    bool isMouseRelative();


    Window& setRenderer(const Renderer::Cfg& recreatenderer_cfg);
    Window& setTitle(const char* title);
    Window& setSize(Vec2i size);
    Window& setPosition(Vec2i position);
    Window& setResizable(bool yes = true);
    Window& setMaximized(bool yes = true);  Window& toggleMaximized();
    Window& setMinimized(bool yes = true);
    Window& setFullScreen(bool yes = true);
    Window& setBorderless(bool yes = true);
    Window& setHidden(bool yes = true);
    Window& setAlwaysOnTop(bool yes = true);
    Window& setKeyboardGrabbed(bool yes = true);
    Window& setMouseGrabbed(bool yes = true);
    Window& setMouseRelative(bool yes = true);

private:
    template<Trait> consteval static inline uint64 M_ToSDL3WindowFlag();
    static inline uint64 M_ToSDL3WindowFlagRuntime(uint64 traits);
};


enum MK_NODISCARD Window::Trait : uint64 {
    NONE = 0,

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


NAMESPACE_END(cone)
