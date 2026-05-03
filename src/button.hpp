#pragma once

#include <SDL3/SDL.h>

class Button {

    SDL_FRect rect;
    SDL_Color baseColor;
    SDL_Color hoverColor;
    bool isHover = false;

public:
    
    Button(float x, float y, float w, float h, SDL_Color color);

    void update(float mouseX, float mouseY);
    void draw(SDL_Renderer* renderer);

    bool isHovering() const;
};