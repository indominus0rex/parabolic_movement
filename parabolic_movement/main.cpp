#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <fmt/core.h>
#include <vector>
#include <iostream>

#include "window.h"
#include "button.h"

struct Particle {
    float x;
    float y;
    float vx;
    float vy;
    bool active;
    SDL_Color color;

    Particle(int x, int y, int ux, int uy) : x(x), y(y), vx(ux), vy(uy), active(true) { color = {255, 255, 255}; }

    void update(float deltaTime) {
        if (!active) return;

        //apply gravity
        const float gravity = 9.8f * 100.0f;
        vy += gravity * deltaTime;

        //change position
        x += vx * deltaTime;
        y += vy * deltaTime;
    }

    void draw(SDL_Renderer* renderer) {
        if (!active) return;

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_FRect rect = { x, y, 5.0f, 5.0f };
        SDL_RenderFillRect(renderer, &rect);
    }
};

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    Window* window = new Window("Title", 1280, 960, 640, 480, SDL_WINDOW_RESIZABLE);

    Button spawnButton(window->logWidth() - 80, window->logHeight() - 30, 50, 20, {0, 102, 204, 255});

    bool running = true;
    float prevTime = SDL_GetTicks() / 1000.0f;

    std::vector<Particle> particles;
    
    while (running) {
    
        float currentTime = SDL_GetTicks() / 1000.0f;
        float deltaTime = currentTime - prevTime;
        prevTime = currentTime;
        
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_EVENT_QUIT: {
                    running = false;
                    break;
                }

                case SDL_EVENT_WINDOW_RESIZED: {
                    int tempW, tempH;
                    SDL_GetWindowSize(window->getWindow(), &tempW, &tempH);
                    window->setSize(tempW, tempH);
                    break;
                }

                case SDL_EVENT_WINDOW_ENTER_FULLSCREEN || SDL_EVENT_WINDOW_LEAVE_FULLSCREEN: {
                    window->toggleFullscreen();
                    break;
                }

                case SDL_EVENT_MOUSE_MOTION: {
                    SDL_ConvertEventToRenderCoordinates(window->getRenderer(), &event);

                    float mouseX = event.button.x;
                    float mouseY = event.button.y;
                    spawnButton.update(mouseX, mouseY);
                    
                    break;
                }

                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    if (spawnButton.isHover) 
                        particles.push_back(Particle(10, window->logHeight() - 100, 300, -800));
        
                    break;
                }
            }
        }

        
        //cleanup previous frame
        window->cleanup(20, 10, 30);
        
        //display particle spawn button
        spawnButton.draw(window->getRenderer());
        
        //update particles
        for (auto& particle : particles) {
            particle.update(deltaTime);
            particle.draw(window->getRenderer());
        }

        //display time elapse
        SDL_SetRenderDrawColor(window->getRenderer(), 255, 255, 255, 255);
        SDL_RenderDebugText(window->getRenderer(), 10, 10, fmt::format("Current Time = {:.3f}s", currentTime).c_str());
    
        
        //update frame
        window->updateFrame();
    }

    delete window;
    
    SDL_Quit();

    return 0;
}