#include "world.h"
#include <SDL3/SDL_rect.h>
#include <algorithm>
#include "vec.h"
#include "physics.h"

World::World(int width, int height)
    : tilemap{width, height} {}

void World::add_platform(float x, float y, float width, float height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tilemap(x+j, y+i) = Tile::Platform;
        }
    }
}


bool World::collides(const Vec<float> &position) const {
    int x =  std::floor(position.x);
    int y =  std::floor(position.y);

    // Check bounds
    if (x < 0 || x >= tilemap.width || y < 0 || y >= tilemap.height) {
        return true;  // collision
    }

    return tilemap(x, y) == Tile::Platform;
}

GameObject* World::create_player() {
    player = std::make_unique<GameObject>(Vec<float>{10, 5}, Vec<int>{1, 1}, *this);
    return player.get();
}

void World::update(float dt) {
    // currently only updating player
    auto position = player->physics.position;
    auto velocity = player->physics.velocity;
    auto acceleration = player->physics.acceleration;

    velocity += 0.5f * acceleration * dt;
    position += velocity * dt;
    velocity += 0.5f * acceleration * dt;
    velocity.x *= player->physics.damping;

    velocity.x = std::clamp(velocity.x, -player->physics.terminal_velocity, player->physics.terminal_velocity);
    velocity.y = std::clamp(velocity.y, -player->physics.terminal_velocity, player->physics.terminal_velocity);

    // check for x collisions
    Vec<float> future_position{position.x, player->physics.position.y};
    Vec<float> future_velocity{velocity.x, 0};
    move_to(future_position, player->size, future_velocity);

    // y collisions
    future_velocity.y = velocity.y;
    future_position.y = position.y;
    move_to(future_position, player->size, future_velocity);

    // Update the player position and velocity
    player->physics.position = future_position;
    player->physics.velocity = future_velocity;
}

void World::move_to(Vec<float>& position, const Vec<int>& size, Vec<float>& velocity) {
    // test for collisions on the bottom or top first
    if (velocity.y >= 0) { // Moving down
        // Check bottom
        Vec<float> bottom_pos =  {position.x, position.y + size.y};
        if (collides(bottom_pos)) {
            position.y = floor(position.y);
            velocity.y = 0;
        }
    }
    else if (velocity.y <= 0) { // Up
        // Check top
        Vec<float> top_pos = {position.x, position.y};
        if (collides(top_pos)) {
            position.y = ceil(position.y);
            velocity.y = 0;
        }
    }

    // then test for collisions on the left and right sides
    if (velocity.x >= 0) { // To the right
        // Check right
        Vec<float> right_pos = {position.x + size.x, position.y};
        if (collides(right_pos)) {
            position.x = floor(position.x);
            velocity.x = 0;
        }

    }
    else if (velocity.x <= 0) { // Left
        // Check left
        Vec<float> left_pos = {position.x, position.y};
        if (collides(left_pos)) {
            position.x = ceil(position.x);
            velocity.x = 0;
        }
    }

    // now test each corner
    if (velocity.x != 0 && velocity.y != 0) {
        Vec <float> corner_pos = {position.x, position.y};
        if (collides(corner_pos)) {
            // Calculate nearest edge for each axis
            float dx = ceil(position.x) - position.x;
            float dy = ceil(position.y) - position.y;

            // Pick the axis with smaller pen
            if (dx > dy) {
                position.y = floor(position.y);
                velocity.y = 0;
            }
            else {
                position.x = floor(position.x);
                velocity.x = 0;
            }
        }
    }
}


//*_
//| |
//-
// pos.x = size.x, pos.y
// pos.y = ceil(pos.y)
// vel.7 = 0
//
//
//  *//