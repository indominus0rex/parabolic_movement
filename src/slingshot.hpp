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
    bool mouseDown;

    glm::vec2 defaultMousePosition = glm::vec2(-1, -1);

    void drawArrow(SDL_Renderer* renderer, glm::vec2 start, glm::vec2 end, float thickness, float headSize) {
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

    void createNewParticle(Window* window, std::vector<std::unique_ptr<Object>> &objects) {
        float velocityY = (endPosition.y - startPosition.y);
        float velocityX = (endPosition.x - startPosition.x);
        float mass = 1;
        float sizeX = 10;
        float sizeY = 10;
        float new_positionX = (startPosition.x - sizeX / 2);
        float new_positionY = (startPosition.y - sizeY / 2);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<Uint8> distr(0, 255);
        SDL_Color color = {distr(gen), distr(gen), distr(gen), distr(gen)};

        Particle particle(new_positionX, new_positionY, sizeX, sizeY, velocityX, velocityY, mass, color);
        objects.push_back(std::make_unique<Particle>(particle));
    }

public:

    Slingshot();

    void update(Window* window, float deltaTime) override;
    void draw(SDL_Renderer* renderer);
    void handleEvents(Window* window, SDL_Event& event, std::vector<std::unique_ptr<Object>>& objects);
};