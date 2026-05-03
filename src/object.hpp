#pragma once

#include <SDL3/SDL.h>

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

    Object(float x, float y, float w, float h);

    virtual ~Object() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(SDL_Renderer* renderer) = 0;

    bool checkCollision(float otherX, float otherY, float otherW, float otherH) const;
};

class Particle : public Object {
public:
    
    using Object::Object;
    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
};

class Button : public Object {
public:

    using Object::Object;
    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
};