#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <variant>
#include <random>

#include "window.hpp"
#include "object.hpp"
#include "config.hpp"

class Particle : public Object {
private:
    
    glm::vec2 velocity;
    float mass;

    void calcNewVelocity(Particle* other);
    void handleAABBCollision(Window* window, Particle* other);
    void resolveCollision(Window* window, Particle* other);
    void drawCircle(SDL_Renderer* renderer);

public:
    
    Particle(const ParticleConfig& particleConfig);

    ~Particle();

    void update(Window* window, float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
    void onCollision(Window* window, Object* other) override;

    //getters
    glm::vec2 getVelocity() const { return velocity; }
    float getMomentum() const { return mass * glm::length(velocity); }
    float getMass() const { return mass; }
    float getRadius() const;
    
    //setters
    void setMass(float mass) { this->mass = mass; }
    void setRadius(float radius);

    template<typename T>
    static void createNewParticle(
        Window* window, 
        std::vector<std::unique_ptr<Object>> &objects, 
        glm::vec2 launchVelocity, 
        glm::vec2 launchPosition
    ) {
        if constexpr (std::is_same_v<T, RectData>) {
            ParticleConfig particleConfig;
            particleConfig.position = launchPosition;
            particleConfig.size = { 10, 10 };
            particleConfig.velocity = launchVelocity;
            particleConfig.mass = 1;
            particleConfig.color = { 255, 255, 255, 255 };
            particleConfig.shapeData = RectData{};

            Particle particle(particleConfig);
            objects.push_back(std::make_unique<Particle>(particle));
        }
        else if constexpr (std::is_same_v<T, CircleData>) {
            ParticleConfig particleConfig;
            particleConfig.center = launchPosition;
            particleConfig.radius = 5;
            particleConfig.velocity = launchVelocity;
            particleConfig.mass = 1;
            particleConfig.color = { 255, 255, 255, 255 };
            particleConfig.shapeData = CircleData{};

            Particle particle(particleConfig);
            objects.push_back(std::make_unique<Particle>(particle));
        }
    }
};