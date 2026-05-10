#include <iostream>
#include <math.h>
#include <algorithm>

#include "particle.hpp"
#include "window.hpp"
#include "object.hpp"

Particle::Particle(float x, float y, float w, float h, float ux, float uy, float mass, SDL_Color color) : 
    Object(x, y, w, h, true) {
        this->mass = mass;
        this->position = glm::vec2(x, y);
        this->size = glm::vec2(w, h);
        this->velocity = glm::vec2(ux, uy);
    }

Particle::~Particle() {}

void Particle::update(Window* window, float deltaTime) {
    const float gravity = 9.8f * 0.01;
    this->velocity.y += gravity;
    this->position += velocity * deltaTime;

    //floor
    if (this->position.y + this->size.y > window->logHeight()) {
        const float velocityYLoss = -0.5f;
        this->velocity.y *= velocityYLoss;
        this->position.y = window->logHeight() - this->size.y;
        
        const float energyLoss = 0.99f;
        this->velocity.x *= energyLoss;

        if (std::abs(this->velocity.x < 0.1f)) {
            this->velocity.x = 0;
        }

        if (std::abs(this->velocity.y < 0.1f)) {
            this->velocity.y = 0;
        }
    }
}

void Particle::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_FRect currentRect = this->getRect();

    SDL_RenderFillRect(renderer, &currentRect);
}

void Particle::onCollision(Window* window, Object* other) {
    //hit another particle  
    if (Particle* p = dynamic_cast<Particle*>(other)) {
        if (!p->getCanCollide() || !this->getCanCollide())
            return;
            
        SDL_FRect rectA = this->getRect();
        SDL_FRect rectB = p->getRect();
        SDL_FRect rectC;
        
        SDL_GetRectIntersectionFloat(&rectA, &rectB, &rectC);
        
        if (rectC.w < rectC.h) {
            if (this->position.x < p->position.x) {
                this->position.x -= rectC.w;
            }
            else if (this->position.x > p->position.x) {
                this->position.x += rectC.w;
            }
        }
        else if (rectC.w > rectC.h) {
            if (this->position.y > p->position.y) {
                this->position.y += rectC.h / 2.0f;
                p->position.y -= rectC.h / 2.0f;
                if (this->position.y + this->size.y > window->logHeight()) 
                    this->position.y = window->logHeight() - this->size.y;
            }
            else if (this->position.y < p->position.y) {
                p->position.y += rectC.h /= 2.0f;
                this->position.y -= rectC.h / 2.0f;
                this->velocity.y *= -0.5f;
            }

            const float energyLoss = 0.99f;
            this->velocity *= energyLoss;
        }
    }
}