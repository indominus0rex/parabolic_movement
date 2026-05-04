#pragma once

#include <SDL3/SDL.h>

#include "object.hpp"

class Button : public Object {
public:

    SDL_FRect rect;
    SDL_Color baseColor;
    SDL_Color hoverColor;
    bool isHover;
    
    
    Button(float x, float y, float w, float h, SDL_Color color);

    ~Button();

    void draw(SDL_Renderer* renderer) override;
    void handleEvents(const SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window) override;
};