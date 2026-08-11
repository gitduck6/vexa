#pragma once
#include <concepts>
#include <string_view>
#include <type_traits>

namespace ecs {

// The compile-time contract. Nothing here is optional and nothing here
// requires the user to opt in manually — Entity<Derived> checks this for you.
template <typename T>
concept EntityShape = requires(T& e) {
    { e.start()  } -> std::same_as<void>;
    { e.input()  } -> std::same_as<void>;
    { e.update() } -> std::same_as<void>;
    { e.render() } -> std::same_as<void>;
    { e.finish() } -> std::same_as<void>;

    { e.resource } -> std::convertible_to<std::string_view>;

    requires std::is_array_v<decltype(e.pos)>;
    requires std::extent_v<decltype(e.pos)> == 2;
    requires std::same_as<std::remove_extent_t<decltype(e.pos)>, float>;

    requires std::is_array_v<decltype(e.scale)>;
    requires std::extent_v<decltype(e.scale)> == 2;
    requires std::same_as<std::remove_extent_t<decltype(e.scale)>, float>;
};

} // namespace ecs
