#include <iostream>
#include <math.h>
#include <algorithm>

#include "particle.hpp"
#include "window.hpp"
#include "object.hpp"

Particle::Particle(float x, float y, float w, float h, float ux, float uy, float mass, SDL_Color color) : 
    Object(x, y, w, h, color, true) {
        this->mass = mass;
        this->velocity = glm::vec2(ux, uy);
    }

Particle::~Particle() {}

void Particle::update(Window* window, float deltaTime) {
    const float gravity = 9.8f * 100;
    this->velocity.y += gravity * deltaTime;
    this->position += velocity * deltaTime;

    //floor
    if (this->position.y + this->size.y > window->logHeight()) {
        this->position.y = window->logHeight() - this->size.y;
        if (this->velocity.y)
            this->velocity.y *= -0.5f;
    }

    //ceiling
    if (this->position.y < 0) {
        this->position.y = 0;
        if (this->velocity.y)
            this->velocity.y *= -0.5f;
    }

    //left wall
    if (this->position.x < 0) {
        this->position.x = 0;
        if (this->velocity.x)
            this->velocity.x *= -0.5f;
    }

    //right wall
    if (this->position.x + this->size.x > window->logWidth()) {
        this->position.x = window->logWidth() - this->size.x;
        if (this->velocity.x)
            this->velocity.x *= -0.5f;
    }
}

void Particle::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect currentRect = this->getRect();
    SDL_RenderFillRect(renderer, &currentRect);
}

void AABBCollisionHandle(Particle* otherParticle) {
    
}

void Particle::onCollision(Window* window, Object* other) {
    //hit another particle
    if (other->getType() == ObjectType::PARTICLE) {
        Particle* otherParticle = static_cast<Particle*>(other);

        this->calcNewVelocity(otherParticle);
        otherParticle->calcNewVelocity(this);

        AABBCollisionHandle(otherParticle);
    }
}