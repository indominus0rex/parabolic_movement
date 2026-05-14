#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "drawObjects.hpp"
#include "window.hpp"
#include "object.hpp"

void DrawObjects::draw(SDL_Renderer* renderer) {

}  

void DrawObjects::handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && currentMode == InputMode::DRAW) {
        mouseDown = true;
        std::visit(Overload{
            [&](DrawObjectRectData& rect) {
                rect.startPosition = this->getMousePosition(window, event);
            },
            [&](DrawObjectLineData& line) {
                line.previousMousePosition = this->getMousePosition(window, event);
                line.vertices.push_back(this->getMousePosition(window, event));
            }
        }, drawData);
    }

    if (event.type == SDL_EVENT_MOUSE_MOTION && mouseDown) {
        std::visit(Overload{
            [&](DrawObjectRectData& rect) {
                rect.endPosition = getMousePosition(window, event);
            },
            [&](DrawObjectLineData& line) {
                line.vertices.push_back(getMousePosition(window, event));
                line.previousMousePosition = getMousePosition(window, event);
            }
        }, drawData);
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && mouseDown) {
        mouseDown = false;
        std::visit(Overload{
            [&](DrawObjectRectData& rect) {
                SDL_FRect newRect = rect.getRect();
                SDL_RenderFillRect(window->getRenderer(), &newRect);
            },
            [&](DrawObjectLineData& line) {
                SDL_RenderLines(window->getRenderer(), (SDL_FPoint* ) line.vertices.data(), (int) line.vertices.size());
            }
        }, drawData);
    }
}