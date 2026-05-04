#include <iostream>
#include <math.h>

#include "particle.hpp"
#include "window.hpp"
#include "object.hpp"

Particle::Particle(float x, float y, float w, float h, float ux, float uy, float mass, SDL_Color color) : 
    Object(x, y, w, h, true, true), rect({x, y, w, h}), vx(ux), vy(uy), color(color), momentum(mass * sqrt(ux * ux + uy * uy)) {}

Particle::~Particle() {}

void Particle::update(Window* window, float deltaTime) {
    const float gravity = 9.8f * 100.0f;
    vy += gravity * deltaTime;

    x += vx * deltaTime;
    y += vy * deltaTime;
}

void Particle::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = { x, y, 5.0f, 5.0f };
    SDL_RenderFillRect(renderer, &rect);
}

void Particle::onCollision(Object* other) {
    //hit another particle  
    if (dynamic_cast<Particle*>(other)) {
        Particle* b = dynamic_cast<Particle*>(other);
    }
}