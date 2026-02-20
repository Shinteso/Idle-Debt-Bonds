//
// Created by LJ on 2/12/2026.
//
#include "game_object.h"
#include "physics.h"
#include "world.h"
#include "fsm.h"
#include "Action.h"

GameObject::GameObject(const Vec<float>& position, const Vec<int>& size, World& world, FSM* fsm, Color)
    : physics{position,{0,0}, {0,0}}, size{size}, fsm{fsm}, color{color} {
        physics.acceleration.y = physics.gravity;
        fsm->current_state->on_enter(world, *this);
}

GameObject::~GameObject() {
    delete fsm;
}


void GameObject::input(World& world) {
    const bool *key_states  = SDL_GetKeyboardState(NULL);
    // if (key_states[SDL_SCANCODE_A]) {
    //     physics.acceleration.x += -physics.walk_acceleration;
    // }
    // if (key_states[SDL_SCANCODE_D]) {
    //     physics.acceleration.x += physics.walk_acceleration;
    // }

    ActionType action_type = ActionType::None;
    if (key_states[SDL_SCANCODE_SPACE]) {
        action_type = ActionType::Jump;
    }
    Action* action = fsm->current_state->input(world, *this, action_type);
    if (action != nullptr) {
        action->perform(world, *this);
        delete action;
    }
}


void GameObject::update(World& world, double dt) {
    // Update Player
    fsm->current_state->update(world, *this, dt);
}


std::pair<Vec<float>, Color> GameObject::get_sprite() const {
    return {physics.position, color};
}
