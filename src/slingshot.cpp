#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include <iostream>

#include "particle.hpp"
#include "interaction.hpp"
#include "slingshot.hpp"
#include "window.hpp"
#include "physicsConfig.hpp"

Slingshot::Slingshot(InteractableType interactableType) : mouseDown(false), Interaction(interactableType) {}

void Slingshot::draw(SDL_Renderer* renderer) {
    if (!mouseDown || startPosition == defaultMousePosition || endPosition == defaultMousePosition)
        return;

    drawArrow(renderer, startPosition, endPosition, 2, 5);
}

void Slingshot::handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        mouseDown = true;
        startPosition = getMousePosition(window, event);
        endPosition = getMousePosition(window, event);
    }
    
    if (event.type == SDL_EVENT_MOUSE_MOTION && mouseDown) {
        glm::vec2 mousePosition = getMousePosition(window, event);
        glm::vec2 newEndPosition = { 
            std::max(0.0f, std::min((float) window->logWidth(), mousePosition.x)),
            std::max(0.0f, std::min((float) window->logHeight(), mousePosition.y))
        };

        endPosition = newEndPosition;
    }

    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (mouseDown) {
            mouseDown = false;

            glm::vec2 launchVelocity = {
                (endPosition.x - startPosition.x) * PhysicsConfig::launchForceRatio,
                (endPosition.y - startPosition.y) * PhysicsConfig::launchForceRatio
            };

            // Particle::createNewParticle<RectData>(window, objects, launchVelocity, startPosition);
            Particle::createNewParticle<CircleData>(window, objects, launchVelocity, startPosition);
        }
    }
}

void Slingshot::drawArrow(SDL_Renderer* renderer, glm::vec2 start, glm::vec2 end, float thickness, float headSize) {
    float dx = end.x - start.x;
    float dy = end.y - start.y;
    float length = sqrt(dx * dx + dy * dy);
    if (length < 1.0f) return;

    float ux = dx / length; // Unit vector along the line
    float uy = dy / length;
    float nx = -uy;         // Perpendicular Normal
    float ny = ux;

    SDL_FPoint headBase = { end.x - ux * headSize, end.y - uy * headSize };

    SDL_FColor col = { 1.0f, 1.0f, 1.0f, 1.0f }; // White
    SDL_Vertex v[7];

    // --- SHAFT (Rectangle) ---
    v[0] = { {start.x + nx * thickness/2, start.y + ny * thickness/2}, col, {0,0} };
    v[1] = { {start.x - nx * thickness/2, start.y - ny * thickness/2}, col, {0,0} };
    v[2] = { {headBase.x + nx * thickness/2, headBase.y + ny * thickness/2}, col, {0,0} };
    v[3] = { {headBase.x - nx * thickness/2, headBase.y - ny * thickness/2}, col, {0,0} };

    // --- HEAD (Triangle) ---
    v[4] = { {end.x, end.y}, col, {0,0} }; // The Tip
    v[5] = { {headBase.x + nx * headSize, headBase.y + ny * headSize}, col, {0,0} }; // Left wing
    v[6] = { {headBase.x - nx * headSize, headBase.y - ny * headSize}, col, {0,0} }; // Right wing
    
    // Shaft: (0,1,2) and (1,2,3) | Head: (4,5,6)
    int indices[] = { 0, 1, 2, 1, 2, 3, 4, 5, 6 };

    SDL_RenderGeometry(renderer, NULL, v, 7, indices, 9);
}