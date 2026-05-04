#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <random>

#include "button.hpp"
#include "object.hpp"
#include "particle.hpp"
#include "window.hpp"

Button::Button(float x, float y, float w, float h, SDL_Color color) : Object(x, y, w, h, false), rect({x, y, w, h}), baseColor(color) {
    hoverColor = { (Uint8)(color.r + 20), (Uint8)(color.g + 20), (Uint8)(color.b + 20), 255 };
}

Button::~Button() {}

void Button::draw(SDL_Renderer* renderer) {
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

void Button::handleEvents(const SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (isHover) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<Uint8> distr(0, 255);
            objects.push_back(std::make_unique<Particle>(0, 30, 10, 10, 100, 0, 1, SDL_Color{distr(gen), distr(gen), distr(gen), 255}));
        }
    }

    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        float mouseX;
        float mouseY;

        SDL_RenderCoordinatesFromWindow(window->getRenderer(), event.button.x, event.button.y, &mouseX, &mouseY);

        isHover = rect.x <= mouseX && mouseX <= rect.x + rect.w && rect.y <= mouseY && mouseY <= rect.y + rect.h;
    }
}