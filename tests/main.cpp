#include "cone.hpp"

int main()
{
    IF_THEN(not
        cone::Engine::Init(cone::Engine::VIDEO | cone::Engine::EVENT),
        cone::log::fatal("Engine didnt start");
    );

    cone::Window::Cfg window_cfg;
    cone::Renderer::Cfg renderer_cfg;
    window_cfg.size = {1, 1};
    auto window = cone::Window{window_cfg}.setRenderer(renderer_cfg).create();
    auto& gfx = window.renderer();

    while(true)
    {
        gfx.start(cone::ColorF32::BLACK);
        gfx.rectFill({{132, 453}, {132, 343}}, cone::ColorU8::RED);
        gfx.finish();
        cone::time::sleep(cone::time::Millis{16.6});
    }

    cone::Engine::Close();
}
