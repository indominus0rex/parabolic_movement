#pragma once

#include <SDL3/SDL.h>
#include <string>

class Button {

public:
    SDL_FRect rect;
    SDL_Color baseColor;
    SDL_Color hoverColor;
    bool isHover = false;

    Button(float x, float y, float w, float h, SDL_Color color) : rect({x, y, w, h}), baseColor(color) {
        hoverColor = { (Uint8)(color.r + 20), (Uint8)(color.g + 20), (Uint8)(color.b + 20), 255 };
    }

    void update(float mouseX, float mouseY) {
        isHover = rect.x <= mouseX && mouseX <= rect.x + rect.w && rect.y <= mouseY && mouseY <= rect.y + rect.h;
    }

    void draw(SDL_Renderer* renderer) {
        if (isHover) 
            SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
        else 
            SDL_SetRenderDrawColor(renderer, baseColor.r, baseColor.g, baseColor.b, baseColor.a);

        SDL_RenderFillRect(renderer, &rect);
        
        //draw text
        std::string spawnText = "SPAWN";
        float textWidth = (float) spawnText.length() * 8.0f;
        float textHeight = 8.0f;

        float textX = rect.x + (rect.w - textWidth) / 2;
        float textY = rect.y + (rect.h - textHeight) / 2;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDebugText(renderer, textX, textY, "SPAWN");
    }
};