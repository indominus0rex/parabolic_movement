#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include <iostream>

#include "slingshot.hpp"

Slingshot::Slingshot(float x, float y, float w, float h) : Object(x, y, w, h, false) {}

void Slingshot::draw(SDL_Renderer* renderer) {
    if (startPosition == glm::vec2(-1, -1) || endPosition == glm::vec2(-1, -1))
        return;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderLine(renderer, startPosition.x, startPosition.y, endPosition.x, endPosition.y);
}

void Slingshot::handleEvents(const SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        glm::vec2 mousePosition;

        std::cout << "working" << '\n';

        SDL_RenderCoordinatesFromWindow(window->getRenderer(), event.button.x, event.button.y, &mousePosition.x, &mousePosition.y);

        if (startPosition.x == -1 && startPosition.y == -1) {
            startPosition = mousePosition;
        }
        else {
            endPosition = mousePosition;
        }   
    }    

    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        glm::vec2 mousePosition = glm::vec2(-1, -1);
        startPosition = mousePosition;
        endPosition = mousePosition;
    }
}

void Slingshot::update(Window* window, float deltaTime) {

}