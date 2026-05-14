#pragma once

#include <SDL3/SDL.h>
#include <functional>

#include "object.hpp"
#include "interaction.hpp"

class Button : public Interaction, Object {
protected:
    
    SDL_Color hoverColor;

public:


    std::function<void()> onClick;

    Button(glm::vec2 position, glm::vec2 size, SDL_Color color, std::function<void()> callback);

    ~Button();

    void draw(SDL_Renderer* renderer) override;
    void handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects) override;
};