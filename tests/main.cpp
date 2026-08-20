#include "monako.hpp"

int main()
{
    IF_THEN(not
        monako::Engine::Init(monako::Engine::VIDEO | monako::Engine::EVENT),
        monako::log::fatal("Engine didnt start");
    );

    monako::Window::Cfg window_cfg;
    monako::Renderer::Cfg renderer_cfg;
    window_cfg.size = {1, 1};
    auto window = monako::Window{window_cfg}.setRenderer(renderer_cfg).create();
    auto& gfx = window.renderer();

    while(true)
    {
        gfx.start(monako::ColorF32::BLACK);
        gfx.rectFill({{132, 453}, {132, 343}}, monako::ColorU8::RED);
        gfx.finish();
        monako::time::sleep(monako::time::Millis{16.6});
    }

    monako::Engine::Close();
}
