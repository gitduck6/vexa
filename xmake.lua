--- RULES/POLICIES
add_rules("mode.debug", "mode.release"); set_defaultmode("debug")
add_rules("plugin.compile_commands.autoupdate")
set_policy("build.progress_style", "multirow")
-- add_rules("c++.unity_build")

--- TOOLCHAIN
toolchain("cone-llvm")
    set_kind("standalone"); set_toolset("cxx", "clang++");
    set_toolset("as",    "clang"); set_toolset("ar",    "llvm-ar")
    set_toolset("ld",    "clang++"); set_toolset("sh",    "clang++")
    set_toolset("ex",    "clang++"); set_toolset("strip", "llvm-strip")
toolchain_end()

set_toolchains("cone-llvm")


--- SCRIPT-BEGIN
    flags = {"-Wall"}

    if is_mode("debug") then
        set_optimize("none")
        set_symbols("debug")
        set_strip("none")
        debug = true
        flags = {
            "-Wall", "-Wextra",
            "-fno-exceptions",
            -- "-Wno-unused-function",
            -- "-Wno-unused-variable",
            -- "-Wno-unused-const-variable",
        };
    elseif is_mode("release") then
        set_optimize("fastest")
        set_symbols("none")
        set_strip("all")
        debug = false
        flags = {
            "-Wall",
            "-fno-exceptions",
        };

    end

--- SCRIPT-END


--- DEPENDENCIES
add_requires("libsdl3", {system = true})

--- GLOBAL
set_languages("c++23")
add_includedirs("include/")
add_cxxflags(table.unpack(flags))
add_ldflags("-flto=full")
add_cxxflags("-stdlib=libc++")
add_ldflags("-stdlib=libc++")
add_defines("_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_DEBUG")

--- TARGETS
target("cone")
    set_kind("object")
    add_files("src/*.cpp")
    add_packages("libsdl3")

target("game")    add_files("tests/game.cpp")    add_deps("cone")
target("main")    add_files("tests/main.cpp")    add_deps("cone")
target("meter")    add_files("tests/meter.cpp")    add_deps("cone")
target("cstrlen") add_files("tests/cstrlen.cpp") add_deps("cone")
target("size") add_files("tests/item_size.cpp") add_deps("cone")
target("ref") add_files("tests/ref.cpp") add_deps("cone")
target("sdl")     add_files("tests/sdl3.cpp")    add_deps("cone")
target("bound")     add_files("tests/bound.cpp")    add_deps("cone")
target("time")    add_files("tests/time.cpp")    add_deps("cone")
target("entity")  add_files("tests/entity.cpp")  add_deps("cone")
