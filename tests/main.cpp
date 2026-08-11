#include "monako.hpp"

int main()
{
    IF_THEN(not
        monako::Engine::Init(monako::Engine::VIDEO | monako::Engine::EVENT),
        monako::log::fatal("Engine didnt start");
    );

    monako::Window window;
    monako::Renderer::Cfg renderer_cfg;
    window.setRenderer(renderer_cfg);
    window = window.create();
    monako::Renderer& gfx = window.renderer();

    while(true)
    {
        gfx.start();
        gfx.rectFill({{132, 453}, {132, 343}}, monako::ColorU8::RED);
        gfx.finish();
    }

    monako::Engine::Close();
}
