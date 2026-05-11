#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include "interaction.hpp"

class Slingshot : public Interaction {
protected:

    glm::vec2 startPosition;
    glm::vec2 endPosition;

public:

    Slingshot() {}
    Slingshot(float x, float y, float w, float h);

    void update(Window* window, float delaTime) override;
    void draw(SDL_Renderer* renderer) override;
    void handleEvents(const SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window) override;
};