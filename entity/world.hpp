#pragma once
#include <algorithm>
#include <concepts>
#include <tuple>
#include <utility>
#include <vector>

#include "entity.hpp"
#include "entity_concept.hpp"

namespace ecs {

// Second line of defense: even if someone constructs an entity outside a
// World, Entity<Derived>'s constructor already caught a malformed type.
// This constraint just means World will refuse to even name the type,
// giving a short concept-diagnostic instead of a template-instantiation
// wall of text.
template <typename T>
concept ValidEntity = EntityShape<T> && std::derived_from<T, Entity<T>>;

// Fixed, compile-time set of entity types. Every type gets its own
// contiguous std::vector<T> — no type erasure, no virtual dispatch,
// no RTTI. Iteration is a fold expression unrolled over the pools.
template <ValidEntity... Types>
class World {
public:
    template <ValidEntity T, typename... Args>
        requires (std::same_as<T, Types> || ...)
    T& create(Args&&... args) {
        auto& pool = std::get<std::vector<T>>(pools_);
        return pool.emplace_back(std::forward<Args>(args)...);
    }

    void start_all()  { for_each_entity([](auto& e) { e.start();  }); }
    void input_all()  { for_each_entity([](auto& e) { e.input();  }); }
    void update_all() { for_each_entity([](auto& e) { e.update(); }); }
    void render_all() { for_each_entity([](auto& e) { e.render(); }); }
    void finish_all() { for_each_entity([](auto& e) { e.finish(); }); }

    void tick() { input_all(); update_all(); render_all(); }

    template <ValidEntity T>
    std::vector<T>& pool() { return std::get<std::vector<T>>(pools_); }

private:
    template <typename F>
    void for_each_entity(F&& f) {
        std::apply([&](auto&... pool) {
            (std::ranges::for_each(pool, f), ...);
        }, pools_);
    }

    std::tuple<std::vector<Types>...> pools_;
};

} // namespace ecs
