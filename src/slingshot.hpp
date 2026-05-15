#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <memory>
#include <random>
#include <vector>

#include "interaction.hpp"
#include "window.hpp"

class Slingshot : public Interaction {
protected:

    glm::vec2 startPosition;
    glm::vec2 endPosition;
    bool mouseDown = false;
    const glm::vec2 defaultMousePosition = glm::vec2(-1, -1);

    void drawArrow(SDL_Renderer* renderer, glm::vec2 start, glm::vec2 end, float thickness, float headSize);

public:

    Slingshot(InteractableType interactableType);

    void draw(SDL_Renderer* renderer);
    void handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects);
};