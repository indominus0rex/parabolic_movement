#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <random>

#include "button.hpp"
#include "object.hpp"
#include "particle.hpp"
#include "window.hpp"
#include "config.hpp"

Button::Button(const ButtonConfig& buttonConfig) : Object(buttonConfig), Interaction(buttonConfig.interactabletype) {
    this->hoverColor = {
        Uint8(color.r + 20),
        Uint8(color.g + 20),
        Uint8(color.b + 20),
        Uint8(color.a)
    };

    this->onClick = buttonConfig.onClick;
}   

Button::~Button() {}

void Button::draw(SDL_Renderer* renderer) {
    if (this->isHovered) 
        SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
    else 
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_FRect rect = this->getRect();
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

void Button::handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (this->isHovered) {
            if (this->onClick) {
                this->onClick();
            }
        }
    }

    SDL_FRect rect = this->getRect();

    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        glm::vec2 mousePosition = getMousePosition(window, event);

        this->isHovered = (
            rect.x <= mousePosition.x 
            && mousePosition.x <= rect.x + rect.w 
            && rect.y <= mousePosition.y 
            && mousePosition.y <= rect.y + rect.h
        );
    }
}