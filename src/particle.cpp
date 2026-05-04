#include <iostream>

#include "particle.hpp"
#include "window.hpp"
#include "object.hpp"

Particle::Particle(float x, float y, float w, float h, float ux, float uy, SDL_Color color) : 
    Object(x, y, w, h, true, true), vx(ux), vy(uy), color(color) {}

Particle::~Particle() {}

void Particle::update(Window* window, float deltaTime) {
    const float gravity = 9.8f * 100.0f;
    vy += gravity * deltaTime;

    x += vx * deltaTime;
    y += vy * deltaTime;

    if (x < 0 || x > window->logWidth() || y < 0 || y > window->logHeight()) {
        float x_to_border_left = x;
        float x_to_border_right = window->logWidth() - x;

        if (x_to_border_left > x_to_border_right)
            x = window->logWidth();
        else
            x = 0;
        
        float y_to_border_top = y;
        float y_to_border_bottom = window->logHeight() - y;

        if (y_to_border_bottom > y_to_border_top)
            y = 0;
        else
            y = window->logHeight();
    }
}

void Particle::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = { x, y, 5.0f, 5.0f };
    SDL_RenderFillRect(renderer, &rect);
}

void Particle::handleEvents(const SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window) {}