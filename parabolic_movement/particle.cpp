#include "particle.hpp"
#include "window.hpp"

Particle::Particle() {}
Particle::Particle(float x, float y, float ux, float uy, SDL_Color color) : x(x), y(y), vx(ux), vy(uy), color(color), active(true) {}

void Particle::update(Window* window, float deltaTime) {
        
    if (!active)
        return;

    const float gravity = 9.8f * 100.0f;
    vy += gravity * deltaTime;

    x += vx * deltaTime;
    y += vy * deltaTime;

    if (x < 0 || x > window->logWidth() || y < 0 || y > window->logHeight())
        active = false;
}


void Particle::draw(SDL_Renderer* renderer) {
    if (!active) return;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = { x, y, 5.0f, 5.0f };
    SDL_RenderFillRect(renderer, &rect);
}

void Particle::addParticle(Particle particle) {
    particles.push_back(particle);
}

void Particle::processParticles(Window* window, float deltaTime) {
    auto particle = particles.begin();
    while (particle != particles.end()) {
        particle->update(window, deltaTime);
        particle->draw(window->getRenderer());

        if (!particle->isActive())
            particle = particles.erase(particle);
        else
            ++particle;
    }
}