#include "cone.hpp"
// #include "cone_prelude.hpp"
// #include "alt/SDL3.hpp"

namespace cn = cone;

auto main() -> int
{
    cn::Engine::Init(cn::Engine::VIDEO);

    cn::Window::Cfg window_cfg = {};
    cn::Renderer::Cfg renderer_cfg = {};
    constexpr fp32 dt = 1000.f/60.f;

    auto window = cn::Window {window_cfg}
        .setResizable()
        .setSize({1280, 720})
        .setRenderer(renderer_cfg)
    .create();

    auto& gfx = window.renderer();


    for (;;)
    {
        bool running = true;
        auto begin = cn::time::now();

        while (auto event = cn::Event::Poll()) {
            switch (event->type())
            {
                case cn::Event::QUIT: { running = false; break; }
                case cn::Event::KEY_DOWN: { ; break; }
                case cn::Event::KEY_UP: { ; break; }
                default: { break; }
            }
        }
        if (!running) break;

        gfx.start(cn::ColorU8::BLACK);

        gfx.rectFill({cn::Rect{100, 100, 250, 250}}, cn::ColorU8::CYAN);

        gfx.finish();
        cn::time::sleep(cn::time::Millis(dt - begin.elapsed().millis()));
    }

    cn::Engine::Close();
}
