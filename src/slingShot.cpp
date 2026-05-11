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
    if (!mouseDown || startPosition == defaultMousePosition || endPosition == defaultMousePosition)
        return;

    drawArrow(renderer, startPosition, endPosition, 2, 5);
}

void Slingshot::handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& object) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        mouseDown = true;
        startPosition = getMousePosition(window, event);
        endPosition = getMousePosition(window, event);
    }
    
    if (event.type == SDL_EVENT_MOUSE_MOTION && mouseDown) {
        endPosition = getMousePosition(window, event);
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        mouseDown = false;
        // startPosition = defaultMousePosition;
        // endPosition = defaultMousePosition;
    }
}

void Slingshot::update(Window* window, float deltaTime) {}