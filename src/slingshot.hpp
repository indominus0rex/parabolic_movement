#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "interaction.hpp"
#include "window.hpp"

class Slingshot : public Interaction {
protected:

    glm::vec2 startPosition;
    glm::vec2 endPosition;
    bool mouseDown;

public:

    Slingshot();

    void update(Window* window, float deltaTime) override;
    void draw(SDL_Renderer* renderer);
    void handleEvents(SDL_Event& event, Window* window);
};