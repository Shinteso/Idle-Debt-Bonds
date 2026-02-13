//
// Created by LJ on 2/12/2026.
//
#include "game_object.h"
#include "physics.h"
#include "world.h"

GameObject::GameObject(const Vec<float>& position, const Vec<int>& size, World& world)
    : size{size} {
        physics.position = position;
        physics.acceleration.y = physics.gravity;
}

GameObject::~GameObject() {
}


void GameObject::input(World& world) {
    const bool *key_states  = SDL_GetKeyboardState(NULL);

    physics.acceleration.x = 0;

    if (key_states[SDL_SCANCODE_A]) {
        physics.acceleration.x += -physics.walk_acceleration;
    }
    if (key_states[SDL_SCANCODE_D]) {
        physics.acceleration.x += physics.walk_acceleration;
    }
    if (key_states[SDL_SCANCODE_SPACE]) {
        physics.velocity.y = physics.jump_velocity;
    }
}


void GameObject::update(World& world, double dt) {
    // Update Player

}


std::pair<Vec<float>, Color> GameObject::get_sprite() const {
    return {physics.position, {255, 0, 255, 255}};
}
