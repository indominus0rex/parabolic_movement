#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <variant>
#include <random>

#include "window.hpp"
#include "object.hpp"

class Particle : public Object {
private:
    
    glm::vec2 velocity;
    float mass;

    void calcNewVelocity(Particle* other);
    void handleAABBCollision(Particle* other);
    void drawCircle(SDL_Renderer* renderer);

public:
    
    Particle(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, float mass, SDL_Color color);
    Particle(glm::vec2 center, float radius, glm::vec2 velocity, float mass, SDL_Color color);

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
            float mass = 1;
            float sizeX = 10;
            float sizeY = 10;
        
            glm::vec2 newSize = glm::vec2(sizeX, sizeY);
        
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<Uint8> distr(0, 255);
            SDL_Color color = {distr(gen), distr(gen), distr(gen), distr(gen)};
        
            Particle particle(launchPosition, newSize, launchVelocity, mass, color);
            objects.push_back(std::make_unique<Particle>(particle));
        }
        else if constexpr (std::is_same_v<T, CircleData>) {
            float mass = 1;
            
            float radius = 5;
        
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<Uint8> distr(0, 255);
            SDL_Color color = {distr(gen), distr(gen), distr(gen), distr(gen)};
        
            Particle particle(launchPosition, radius, launchVelocity, mass, color);
            objects.push_back(std::make_unique<Particle>(particle));
        }
    }
};