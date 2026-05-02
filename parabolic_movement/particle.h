#pragma once

#include <SDL3/SDL.h>

#include "window.h"

class Particle {

    float x;
    float y;
    float vx;
    float vy;
    bool active;
    SDL_Color color;
    
public:

    Particle(float x, float y, float ux, float uy, SDL_Color color) : x(x), y(y), vx(ux), vy(uy), active(true), color(color) {}

    void update(Window* window, float deltaTime) {
        
        if (!active)
            return;

        const float gravity = 9.8f * 100.0f;
        vy += gravity * deltaTime;

        x += vx * deltaTime;
        y += vy * deltaTime;

        if (x < 0 || x > window->logWidth() || y < 0 || y > window->logHeight())
            active = false;
    }

    void draw(SDL_Renderer* renderer) {
        if (!active) return;

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_FRect rect = { x, y, 5.0f, 5.0f };
        SDL_RenderFillRect(renderer, &rect);
    }

    bool isActive() const { return active; }
};