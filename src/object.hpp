#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <variant>

#include "window.hpp"

enum ObjectType {
    PARTICLE
};

struct RectData {
    glm::vec2 position;
    glm::vec2 size;
};

struct CircleData {
    glm::vec2 center;
    float radius;
};

class Object {
protected:

    SDL_Color color;
    bool canCollide;
    ObjectType objectType;
    std::variant<RectData, CircleData> shapeData;

public:

    Object(glm::vec2 position, glm::vec2 size, SDL_Color color, bool canCollide);
    Object(glm::vec2 center, float radius, SDL_Color color, bool canCollide);

    virtual ~Object() = default;

    virtual void update(Window* window, float deltaTime) {}
    virtual void draw(SDL_Renderer* renderer) {}
    virtual void handleEvents(const SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window) {}
    virtual void onCollision(Window* window, Object* other) {}

    virtual SDL_Color getColor() { return color; }
    virtual bool getCanCollide() const { return canCollide; }
    virtual ObjectType getType() const { return objectType; }
    virtual SDL_FRect getBoundingBox() const;

    bool isCircle() const { return std::holds_alternative<CircleData>(shapeData); }
    bool isRect() const { return std::holds_alternative<RectData>(shapeData); }
    float getRadius() const;
    glm::vec2 getCenter() const;
    SDL_FRect getRect() const;

    void updatePosition(glm::vec2 positionChanged); 
    void setCenter(glm::vec2 newCenter);
    void setRadius(float newRadius);
};