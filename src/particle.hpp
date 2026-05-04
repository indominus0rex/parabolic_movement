#pragma once

#include <SDL3/SDL.h>
#include <vector>

#include "window.hpp"
#include "object.hpp"

class Particle : public Object {

    float vx;
    float vy;
    float momentum;
    float mass;
    SDL_Color color;
    SDL_FRect rect;
    
public:

    Particle(float x, float y, float w, float h, float ux, float uy, float mass, SDL_Color color);
    
    ~Particle();

    void update(Window* window, float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
    void onCollision(Object* other) override;

    float getMomentum() const { return momentum; }

    SDL_FRect getRect() const { return rect; }
};