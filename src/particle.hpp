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

public:
    
    Particle(float x, float y, float w, float h, float ux, float uy, float mass, SDL_Color color);
    
    ~Particle();

    void update(Window* window, float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
    void onCollision(Window* window, Object* other) override;

    float getMomentum() const { return mass * glm::length(velocity); }

    glm::vec2 getVelocity() const { return velocity; }

    void setMass(float new_mass) { mass = new_mass; }
};