#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <memory>

#include "window.hpp"

class Object {
protected:

    float x;
    float y;
    float w;
    float h;
    SDL_Color color;
    bool dynamic;
    bool canCollide;

public:

    Object(float x, float y, float w, float h, bool dynamic, bool canCollide);

    virtual ~Object() = default;

    virtual void update(Window* window, float deltaTime) {}
    virtual void draw(SDL_Renderer* renderer) {}
    virtual void handleEvents(const SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window) {}

    bool checkCollision(float otherX, float otherY, float otherW, float otherH) const;
};