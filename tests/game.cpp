#include "monako_prelude.hpp"
// #include "alt/SDL3.hpp"

namespace mnk = monako;

auto main() -> int
{
    using monako::Engine;
    using monako::Window;
    using monako::Renderer;
    using monako::Event;
    using monako::ColorU8;
    using monako::Rect;
    namespace time = monako::time;
    namespace log = monako::log;
    Engine::Init(Engine::VIDEO);

    Window::Cfg window_cfg = {};
    Renderer::Cfg renderer_cfg = {};
    constexpr fp32 dt = 1000.f/60.f;

    auto window = Window {window_cfg}
        .setResizable()
        .setSize({1280, 720})
        .setRenderer(renderer_cfg)
    .create();

    auto& gfx = window.renderer();


    for (;;)
    {
        bool running = true;
        auto begin = time::now();

        while (auto event = Event::Poll()) {
            switch (event->type())
            {
                case Event::QUIT: { running = false; break; }
                case Event::KEY_DOWN: { ; break; }
                case Event::KEY_UP: { ; break; }
                default: { break; }
            }
        }
        if (!running) break;

        gfx.start(ColorU8::BLACK);

        gfx.rectFill({Rect{100, 100, 250, 250}}, ColorU8::CYAN);

        gfx.finish();
        time::sleep(time::Millis(dt - begin.elapsed().millis()));
    }

    Engine::Close();
}
