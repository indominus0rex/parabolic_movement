#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include <iostream>

#include "particle.hpp"
#include "interaction.hpp"
#include "slingshot.hpp"
#include "window.hpp"

Slingshot::Slingshot() : mouseDown(false) {}

void Slingshot::draw(SDL_Renderer* renderer) {
    if (startPosition == glm::vec2(-1, -1) || endPosition == glm::vec2(-1, -1))
        return;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderLine(renderer, startPosition.x, startPosition.y, endPosition.x, endPosition.y);
}

void Slingshot::handleEvents(SDL_Event& event, Window* window) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        mouseDown = true;
        startPosition = getMousePosition(window, event);
    }    

    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        mouseDown = false;
    }
}

void Slingshot::update(Window* window, float deltaTime) {
    if (mouseDown) {

    }
}