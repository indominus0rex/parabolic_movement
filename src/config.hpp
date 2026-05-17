#pragma once

#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include "object.hpp"

struct ObjectConfig {   
    glm::vec2 position;
    glm::vec2 size;
    glm::vec2 center;
    float radius;
    SDL_Color color;
    bool canCollide;
};