#pragma once

#include <SDL3/SDL.h>
#include <functional>

#include "object.hpp"
#include "interaction.hpp"
#include "config.hpp"

class Button : public Interaction, Object {
protected:
    
    SDL_Color hoverColor;
    std::function<void()> onClick;

public:

    Button(const ButtonConfig& buttonConfig);

    ~Button();

    void draw(SDL_Renderer* renderer) override;
    void handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects) override;


};