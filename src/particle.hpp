#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>

#include "window.hpp"
#include "object.hpp"

class Particle : public Object {
private:
    
    glm::vec2 velocity;
    float mass;

    float Cr = 0.8f;

    void calcNewVelocity(Particle* other) {
        float mRatio = ((1 + Cr) * other->getMass()) / (mass + other->getMass());
        glm::vec2 vDiff = velocity - other->getVelocity();
        glm::vec2 xDiff = position - other->getPosition();

        float dotProduct = glm::dot(vDiff, xDiff);
        float sqLength = glm::dot(xDiff, xDiff);

        glm::vec2 newVelocity = velocity - mRatio * (dotProduct / (sqLength * sqLength)) * xDiff;
        velocity = newVelocity;
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