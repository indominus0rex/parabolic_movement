#pragma once

#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "interaction.hpp"
#include "window.hpp"

class Slingshot : public Interaction {
protected:

    glm::vec2 startPosition;
    glm::vec2 endPosition;
    bool mouseDown;

    void createNewParticle(std::vector<std::unique_ptr<Object>> &objects) {
        Particle particle(startPosition.x, startPosition.y, 50, 50, glm::distance(startPosition.x, endPosition.x), glm::distance(startPosition.y, endPosition.y), 1, SDL_Color{255, 255, 255, 255});
        objects.push_back(std::make_unique<Particle>(particle));
    }

public:

    Slingshot();

    void update(Window* window, float deltaTime) override;
    void draw(SDL_Renderer* renderer);
    void handleEvents(SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects, Window* window);
};