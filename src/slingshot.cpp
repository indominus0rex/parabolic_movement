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

void Slingshot::handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        mouseDown = true;
        startPosition = getMousePosition(window, event);
        endPosition = getMousePosition(window, event);
    }
    
    if (event.type == SDL_EVENT_MOUSE_MOTION && mouseDown) {
        glm::vec2 mousePosition = getMousePosition(window, event);
        glm::vec2 newEndPosition = { 
            std::max(0.0f, std::min((float) window->logWidth(), mousePosition.x)),
            std::max(0.0f, std::min((float) window->logHeight(), mousePosition.y))
        };

        endPosition = newEndPosition;
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (mouseDown) {
            mouseDown = false;
            createNewParticle(window, objects);
        }
    }
}

void Slingshot::update(Window* window, float deltaTime) {}
