#pragma once

#include <SDL3/SDL.h>
#include <vector>

#include "window.hpp"
#include "object.hpp"

class Particle : public Object {

    float vx;
    float vy;
    SDL_Color color;
    
public:

    Particle(float x, float y, float w, float h, float ux, float uy, SDL_Color color);
    
    ~Particle();

    void update(Window* window, float deltaTime);
    void draw(SDL_Renderer* renderer);
    void handleEvents(const SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window);
};