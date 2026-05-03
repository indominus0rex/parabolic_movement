#pragma once

#include <SDL3/SDL.h>
#include <vector>

#include "window.hpp"

class Particle {

    float x;
    float y;
    float vx;
    float vy;
    bool active;
    SDL_Color color;
    std::vector<Particle> particles;
    
public:

    Particle();
    Particle(float x, float y, float ux, float uy, SDL_Color color);
    
    void update(Window* window, float deltaTime);
    void draw(SDL_Renderer* renderer);
    void addParticle(Particle particle);
    void processParticles(Window* window, float deltaTime);

    bool isActive() const { return active; }
};