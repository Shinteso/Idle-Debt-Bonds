//
// Created by Loonj on 2/13/2026.
//
#include "action.h"
#include "game_object.h"
#include "world.h"

void Jump::perform(World&, GameObject &obj) {
    obj.physics.velocity.y = obj.physics.jump_velocity;
}
