#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "interaction.hpp"

glm::vec2 Interaction::getMousePosition(Window* window, SDL_Event& event) { 
    glm::vec2 mousePosition;
    SDL_RenderCoordinatesFromWindow(window->getRenderer(), event.motion.x, event.motion.y, &mousePosition.x, &mousePosition.y);
    return mousePosition;
}