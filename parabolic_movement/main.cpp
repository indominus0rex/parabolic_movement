<<<<<<< HEAD
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {

    int w = 1280;
    int h = 900;

    SDL_Window *mainWindow;
    SDL_Renderer *mainRenderer;
    mainWindow = SDL_CreateWindow("Title", w, h, SDL_WINDOW_RESIZABLE);
    mainRenderer = SDL_CreateRenderer(mainWindow, nullptr);

    bool running = true;

    while (running) {
=======
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <fmt/core.h>
#include <vector>
#include <iostream>
#include <algorithm>

#include "window.hpp"
#include "button.hpp"
#include "particle.hpp"

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    Window* window = new Window("Title", 1280, 960, 640, 480, SDL_WINDOW_RESIZABLE);

    Button spawnButton(window->logWidth() - 80, window->logHeight() - 30, 50, 20, {0, 102, 204, 255});
    Particle particles;

    bool running = true;
    float prevTime = SDL_GetTicks() / 1000.0f;

    
    while (running) {
    
        float currentTime = SDL_GetTicks() / 1000.0f;
        float deltaTime = currentTime - prevTime;
        prevTime = currentTime;
        
>>>>>>> feature
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_EVENT_QUIT: {
                    running = false;
                    break;
                }
<<<<<<< HEAD
            }
        }

        SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
        SDL_RenderClear(mainRenderer);

        
        SDL_RenderPresent(mainRenderer);
    }

    SDL_DestroyWindow(mainWindow);

=======

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
                    if (spawnButton.isHovering()) {
                        particles.addParticle(Particle(10, window->logHeight() - 100, 300, -800, {255, 255, 255, 255}));
                    }
        
                    break;
                }
            }
        }

        
        //cleanup previous frame
        window->refreshRenderer(20, 10, 30, 255);
        
        //display particle spawn button
        spawnButton.draw(window->getRenderer());
        
        // update particles
        particles.processParticles(window, deltaTime);

        //display time elapse
        SDL_SetRenderDrawColor(window->getRenderer(), 255, 255, 255, 255);
        SDL_RenderDebugText(window->getRenderer(), 10, 10, fmt::format("Current Time = {:.3f}s", currentTime).c_str());
        
        //update frame
        window->updateFrame();
    }

    delete window;
    
>>>>>>> feature
    SDL_Quit();

    return 0;
}