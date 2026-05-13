#include <iostream>
#include <math.h>
#include <algorithm>

#include "particle.hpp"
#include "window.hpp"
#include "object.hpp"

//TODO change x, y, w, h to vec2

Particle::Particle(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, float mass, SDL_Color color) : 
    Object(position, size, color, true), velocity(velocity), mass(mass)  {}

Particle::~Particle() {}

void Particle::update(Window* window, float deltaTime) {
    const float gravity = 9.8f * 100;
    // this->velocity.y += gravity * deltaTime;
    this->position += velocity * deltaTime;

    //floor
    if (this->position.y + this->size.y > window->logHeight()) {
        this->position.y = window->logHeight() - this->size.y;
        if (this->velocity.y)
            this->velocity.y *= -Cr;
    }

    //ceiling
    if (this->position.y < 0) {
        this->position.y = 0;
        if (this->velocity.y)
            this->velocity.y *= -Cr;
    }

    //left wall
    if (this->position.x < 0) {
        this->position.x = 0;
        if (this->velocity.x)
            this->velocity.x *= -Cr;
    }

    //right wall
    if (this->position.x + this->size.x > window->logWidth()) {
        this->position.x = window->logWidth() - this->size.x;
        if (this->velocity.x)
            this->velocity.x *= -Cr;
    }
}

void Particle::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect currentRect = this->getRect();
    SDL_RenderFillRect(renderer, &currentRect);
}

void Particle::onCollision(Window* window, Object* other) {
    //hit another particle
    if (other->getType() == ObjectType::PARTICLE) {
        Particle* otherParticle = static_cast<Particle*>(other);

        glm::vec2 vDiff = velocity - otherParticle->getVelocity();
        glm::vec2 xDiff = position - otherParticle->getPosition();

        if (glm::dot(vDiff, xDiff) >= 0)
            return;

        glm::vec2 v1 = velocity;
        glm::vec2 v2 = otherParticle->getVelocity();
 
        handleAABBCollision(otherParticle);
        
        this->calcNewVelocity(otherParticle);
        otherParticle->calcNewVelocity(this);
    }
}