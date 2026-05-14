#pragma once

#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <variant>
#include <vector>
#include <memory>

#include "window.hpp"
#include "object.hpp"
#include "interaction.hpp"

enum InputMode {
    SHOOT,
    DRAW
};

struct DrawObjectRectData {
    glm::vec2 startPosition;
    glm::vec2 endPosition;
    SDL_Color color;

    SDL_FRect getRect() const {
        return {
            startPosition.x,
            startPosition.y,
            startPosition.x + endPosition.x,
            startPosition.y + endPosition.y
        };
    }
};

struct DrawObjectLineData {
    glm::vec2 previousMousePosition;
    std::vector<glm::vec2> vertices;
    SDL_Color color;
};

class DrawObjects : public Interaction {
protected:

    InputMode currentMode = InputMode::SHOOT;
    bool mouseDown;
    std::variant<DrawObjectRectData, DrawObjectLineData> drawData;

public:

    void draw(SDL_Renderer* renderer) override;
    void handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects) override;

};