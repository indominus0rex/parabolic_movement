#pragma once

#include <SDL3/SDL.h>

#include "window.hpp"

class Particle {

    float x;
    float y;
    float vx;
    float vy;
    bool active;
    SDL_Color color;
    
public:

    Particle(float x, float y, float ux, float uy, SDL_Color color);
    
    void update(Window* window, float deltaTime);
    void draw(SDL_Renderer* renderer);

    bool isActive() const { return active; }
};