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
    glm::vec2 position = { 0.0f, 0.0f };
    glm::vec2 size = { 0.0f, 0.0f };
};

struct CircleData  {
    glm::vec2 center = { 0.0f, 0.0f };
    float radius = 0;
};

struct ObjectConfig {   
    glm::vec2 position = { 0.0f, 0.0f };
    glm::vec2 size = { 0.0f, 0.0f };
    glm::vec2 center = { 0.0f, 0.0f };
    float radius = 0;
    SDL_Color color = { 255, 255, 255, 255 };
    bool canCollide = false;
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