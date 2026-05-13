#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "window.hpp"

enum ObjectType {
    PARTICLE
};

class Object {
protected:

    glm::vec2 position;
    glm::vec2 size;
    SDL_Color color;
    bool canCollide;
    ObjectType objectType;

public:

    Object() {}
    Object(glm::vec2 position, glm::vec2 size, SDL_Color color, bool canCollide);

    virtual ~Object() = default;

    virtual void update(Window* window, float deltaTime) {}
    virtual void draw(SDL_Renderer* renderer) {}
    virtual void handleEvents(const SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window) {}
    virtual void onCollision(Window* window, Object* other) {}

    virtual glm::vec2 getPosition() const { return position; }
    virtual glm::vec2 getSize() const { return size; }
    virtual SDL_Color getColor() { return color; }
    virtual SDL_FRect getRect() { return { position.x, position.y, size.x, size.y };}
    virtual bool getCanCollide() const { return canCollide; }
    virtual ObjectType getType() const { return objectType; }

    virtual void setPosition(float new_x, float new_y) {
        position.x = new_x;
        position.y = new_y;
    }
    virtual void setSize(float new_w, float new_h) {
        size.x = new_w;
        size.y = new_h;
    }
};