#pragma once

#include <glm/glm.hpp>

#include "window.hpp"

class Interaction {
public:

    virtual void update(Window* window, float deltaTime) {}
    virtual ~Interaction() {}

    glm::vec2 getMousePosition(Window* window, SDL_Event& event) { 
        glm::vec2 mousePosition;
        SDL_RenderCoordinatesFromWindow(window->getRenderer(), event.motion.x, event.motion.y, &mousePosition.x, &mousePosition.y);
        return mousePosition;
    }
};