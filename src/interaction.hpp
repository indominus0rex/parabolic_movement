#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <variant>

#include "window.hpp"
#include "object.hpp"

class Interaction {
public:

    template<class... Ts> struct Overload : Ts... { using Ts::operator()...; };
    template<class... Ts> Overload(Ts...) -> Overload<Ts...>;

    virtual void update(Window* window, float deltaTime) {}
    virtual ~Interaction() {}

    virtual void draw(SDL_Renderer* renderer) {}
    virtual void handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects) {}

    glm::vec2 getMousePosition(Window* window, SDL_Event& event) { 
        glm::vec2 mousePosition;
        SDL_RenderCoordinatesFromWindow(window->getRenderer(), event.motion.x, event.motion.y, &mousePosition.x, &mousePosition.y);
        return mousePosition;
    }
};