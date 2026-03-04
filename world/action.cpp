//
// Created by Loonj on 2/13/2026.
//
#include "action.h"
#include "game_object.h"
#include "states.h"
#include "world.h"

void Jump::perform(World&, GameObject &obj) {
    obj.physics.velocity.y = obj.physics.jump_velocity;
}

void MoveRight::perform(World &, GameObject &obj) {
    obj.physics.acceleration.x = obj.physics.walk_acceleration;
}

void MoveLeft::perform(World &, GameObject& obj) {
    obj.physics.acceleration.x = -obj.physics.walk_acceleration;
}

void StageTrans::perform(World &, GameObject& obj) {
    obj.physics.acceleration.x = obj.physics.transition_speed;
}

void Attack::perform(World &, GameObject& obj) {
    obj.physics.acceleration.x = -obj.physics.transition_speed;
}

