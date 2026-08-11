set_languages("c++23") -- bump to c++26 once your toolchain's std flag supports it
add_rules("mode.debug", "mode.release")

target("ecs_demo")
    set_kind("binary")
    add_files("main.cpp")
    add_includedirs(".")
