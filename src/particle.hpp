#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <variant>

#include "window.hpp"
#include "object.hpp"

class Particle : public Object {
private:
    
    glm::vec2 velocity;
    float mass;
    float radius;
    float Cr = 0.8f;

    void calcNewVelocity(Particle* other);
    void handleAABBCollision(Particle* other);
    void handleCircularCollision(Particle* otherParticle);

public:
    
    Particle(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, float mass, SDL_Color color);
    
    ~Particle();

    void update(Window* window, float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
    void onCollision(Window* window, Object* other) override;

    //getters
    glm::vec2 getVelocity() const { return velocity; }
    float getMomentum() const { return mass * glm::length(velocity); }
    float getMass() const { return mass; }
    float getRadius() const { return radius; }

    //setters
    void setMass(float mass) { this->mass = mass; }
    void setRadius(float radius) { this->radius = radius; }
};