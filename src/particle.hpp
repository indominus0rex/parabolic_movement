#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>

#include "window.hpp"
#include "object.hpp"

enum ParticleType {
    Rect,
    Cir
};

class Particle : public Object {
private:
    
    glm::vec2 velocity;
    float mass;
    ParticleType particleType;

    float Cr = 0.8f;

    void calcNewVelocity(Particle* other) {
        float mRatio = ((1 + Cr) * other->getMass()) / (mass + other->getMass());

        glm::vec2 vDiff = velocity - other->getVelocity();
        glm::vec2 xDiff = position - other->getPosition();

        float dotProduct = glm::dot(vDiff, xDiff);
        float sqLength = glm::dot(xDiff, xDiff);

        glm::vec2 newVelocity = velocity - mRatio * (dotProduct / sqLength) * xDiff;
        velocity = newVelocity;
    }

    void handleAABBCollision(Particle* otherParticle) {
        float centerAX = this->position.x + this->size.x / 2.0f;
        float centerAY = this->position.y + this->size.y / 2.0f;
        float centerBX = otherParticle->position.x + otherParticle->size.x / 2.0f;
        float centerBY = otherParticle->position.y + otherParticle->size.y / 2.0f;

        float dx = centerAX - centerBX;
        float dy = centerAY - centerBY;

        float combinedHalfW = (this->size.x + otherParticle->size.x) / 2.0f;
        float combinedHalfH = (this->size.y + otherParticle->size.y) / 2.0f;

        float overlapX = combinedHalfW - std::abs(dx);
        float overlapY = combinedHalfH - std::abs(dy);

        if (overlapX > 0 && overlapY > 0) {
            if (overlapX < overlapY) {
                if (dx > 0) this->position.x += overlapX;
                else this->position.x -= overlapX;
            } else {
                if (dy > 0) this->position.y += overlapY;
                else this->position.y -= overlapY;
            }
        }
    }


public:
    
    Particle(float x, float y, float w, float h, float ux, float uy, float mass, SDL_Color color);
    
    ~Particle();

    void update(Window* window, float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
    void onCollision(Window* window, Object* other) override;

    float getMomentum() const { return mass * glm::length(velocity); }
    float getMass() const { return mass; }
    glm::vec2 getVelocity() const { return velocity; }
    void setMass(float new_mass) { mass = new_mass; }
};