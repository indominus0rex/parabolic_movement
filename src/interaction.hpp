#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <variant>

#include "window.hpp"
#include "object.hpp"

class Interaction {
protected:
    bool isHovered = false;
public:

    virtual ~Interaction() {}
    
    virtual void update(Window* window, float deltaTime) {}
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects) = 0;

    bool getIsHovered() const { return isHovered; }
    glm::vec2 getMousePosition(Window* window, SDL_Event& event);
};