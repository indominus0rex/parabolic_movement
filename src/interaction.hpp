#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <memory>
#include <variant>
#include <string>
#include <functional>

#include "window.hpp"
#include "object.hpp"
#include "config.hpp"

class Interaction {
protected:

    bool isHovered = false;
    InteractableType currentInteractableType;

public:

    Interaction(InteractableType interactableType);

    virtual ~Interaction() {}
    
    virtual void update(Window* window, float deltaTime) {}
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects) = 0;

    InteractableType getType() const { return currentInteractableType; }
    bool getIsHovered() const { return isHovered; }
    glm::vec2 getMousePosition(Window* window, SDL_Event& event);
};