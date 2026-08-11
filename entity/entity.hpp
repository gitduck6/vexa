#pragma once
#include "entity_concept.hpp"

namespace ecs {

// Single-level CRTP. Derived : public Entity<Derived>, nothing else in the chain.
//
// The static_assert lives in OUR constructor, not in user code. Derived is an
// incomplete type at the point Entity<Derived> is instantiated as a base
// (base-specifier list), so the check can't live at class-template scope —
// it has to wait until something actually instantiates the constructor body,
// which only happens once Derived is complete (i.e. the moment a Player,
// Enemy, whatever, is actually constructed). That's still fully automatic:
// the user never writes static_assert, never calls a validator, nothing.
template <typename Derived>
class Entity {
protected:
    Entity() noexcept {
        static_assert(EntityShape<Derived>,
            "ecs::Entity<Derived>: Derived does not satisfy the required entity shape. "
            "It must define void start(), input(), update(), render(), finish(), "
            "and hold members `resource` (string_view-convertible), "
            "`pos` (float[2]), `scale` (float[2]).");
    }

    // Non-virtual, protected dtor: nobody can `delete` through Entity<Derived>*,
    // which is the usual footgun with non-virtual bases. No vtable, ever.
    ~Entity() = default;

    Entity(const Entity&)            = default;
    Entity& operator=(const Entity&) = default;
    Entity(Entity&&)                 = default;
    Entity& operator=(Entity&&)      = default;
};

} // namespace ecs
