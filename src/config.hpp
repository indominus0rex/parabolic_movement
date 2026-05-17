#pragma once

#include <variant>
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <functional>


enum ObjectType {
    PARTICLE
};

enum InteractableType {
    BUTTON,
    SLINGSHOT,
    DRAWOBJECT
};

struct RectData {
    glm::vec2 position;
    glm::vec2 size;
};

struct CircleData  {
    glm::vec2 center;
    float radius;
};

struct ObjectConfig {   
    glm::vec2 position;
    glm::vec2 size;
    glm::vec2 center;
    float radius;
    SDL_Color color;
    bool canCollide;
    std::variant<RectData, CircleData> shapeData;
    ObjectType objectType;
};

struct ButtonConfig : public ObjectConfig {
    InteractableType interactabletype;
    std::function<void()> onClick;
};

struct ParticleConfig : public ObjectConfig {
    glm::vec2 velocity;
    float mass;
};