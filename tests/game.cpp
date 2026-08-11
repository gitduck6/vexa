#include "../include/monako.hpp"
#include "alt/SDL3.hpp"

namespace mnk = monako;

auto main() -> int
{
    using monako::Engine;
    using monako::Window;
    using monako::Renderer;
    using monako::ColorU8;
    using monako::Rect;
    namespace time = monako::time;
    Engine::Init(Engine::VIDEO);

    Window::Cfg window_cfg = {};
    Renderer::Cfg renderer_cfg = {};

    Window window = Window {window_cfg}
        .setRenderer(renderer_cfg)
        .setResizable()
        .setPosition({100, 100})
        .create()
    ;
    // window.setResizable();
    auto& gfx = window.renderer();
    window
        .toggleMaximized().toggleMaximized().toggleMaximized()
        .toggleMaximized().toggleMaximized().toggleMaximized();

    bool running = true;
    while (running) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_EVENT_QUIT: {
                    running = false; break;
                }
                case SDL_EVENT_KEY_DOWN: {
                    switch (ev.key.scancode) {
                        case SDL_SCANCODE_ESCAPE: {
                            running = false; break;
                        }
                        default: {
                            if ((ev.key.mod & SDL_KMOD_CTRL) && ev.key.key == SDLK_Q) {
                                running = false; break;
                            }
                        }
                    }
                }
            }
        }

        gfx.start();
        gfx.clear(ColorU8::BLACK);

        gfx.rectFill({Rect{100, 100, 250, 250}}, ColorU8::CYAN);

        gfx.finish();
        time::sleepMillis(16.6);
    }

    Engine::Close();
}
