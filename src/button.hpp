#pragma once

#include <SDL3/SDL.h>

#include "object.hpp"

class Button : public Object {

    SDL_FRect rect;
    SDL_Color baseColor;
    SDL_Color hoverColor;
    bool isHover;

public:
    
    Button(float x, float y, float w, float h, SDL_Color color);

    ~Button();

    void update(Window* window, float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;
    void handleEvents(const SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window);
};