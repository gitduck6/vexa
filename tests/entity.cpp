#include <cstdio>
#include "../entity/entity.hpp"
#include "../entity/world.hpp"

class Player : public ecs::Entity<Player> {
public:
    std::string_view resource = "player.png";
    float pos[2]   = {0.f, 0.f};
    float scale[2] = {1.f, 1.f};

    void start()  { std::puts("player: start");  }
    void input()  { pos[0] += 1.f; }
    void update() { std::puts("player: update"); }
    void render() { std::printf("player: render at (%.1f, %.1f)\n", pos[0], pos[1]); }
    void finish() { std::puts("player: finish"); }
};

class Enemy : public ecs::Entity<Enemy> {
public:
    std::string_view resource = "enemy.png";
    float pos[2]   = {5.f, 0.f};
    float scale[2] = {1.f, 1.f};

    void start()  { std::puts("enemy: start");  }
    void input()  {}
    void update() { std::puts("enemy: update"); }
    void render() { std::printf("enemy: render at (%.1f, %.1f)\n", pos[0], pos[1]); }
    void finish() { std::puts("enemy: finish"); }
};

// Uncomment to see the guarantee fire — comment out `render()` in Player
// and try to construct one, or try to add a type to World that's missing
// a member. No manual static_assert needed on your end, it just fails.
//
// class Broken : public ecs::Entity<Broken> {
// public:
//     std::string_view resource = "x";
//     float pos[2] = {0,0};
//     float scale[2] = {1,1};
//     void start(){} void input(){} void update(){} void render(){}
//     // finish() missing -> hard compile error at the point of construction
// };

int main() {
    ecs::World<Player, Enemy> world;
    world.create<Player>();
    world.create<Enemy>();

    world.start_all();
    world.tick();
    world.finish_all();
}
