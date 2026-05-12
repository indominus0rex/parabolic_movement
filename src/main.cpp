#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <string>
#include <fmt/core.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

#include "window.hpp"
#include "button.hpp"
#include "particle.hpp"
#include "collisionManager.hpp"
#include "slingshot.hpp"

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    Window* window = new Window("Title", 1280, 720, 640, 360, SDL_WINDOW_RESIZABLE);

    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Object>> particles;

    Slingshot slingshot;

    bool running = true;
    float prevTime = SDL_GetTicks() / 1000.0f;
    
    while (running) {

        float currentTime = SDL_GetTicks() / 1000.0f;
        float deltaTime = currentTime - prevTime;
        prevTime = currentTime;
        
        std::vector<std::unique_ptr<Object>> newObjects;
        std::vector<std::unique_ptr<Object>> newParticles;

        SDL_Event event;
        
        while (SDL_PollEvent(&event)) {

            slingshot.handleEvents(window, event, newParticles);
            
            for (auto& object : objects) {
                Button* button = dynamic_cast<Button*>(object.get());
                
                if (button) {
                    button->handleEvents(event, newParticles, window);
                }
            }

            switch(event.type) {
                case SDL_EVENT_QUIT: {
                    running = false;
                    break;
                }

                case SDL_EVENT_WINDOW_RESIZED: {
                    int tempW, tempH;
                    SDL_GetWindowSize(window->getWindow(), &tempW, &tempH);
                    window->updateSize(tempW, tempH);
                    break;
                }
            }

            if (event.type == SDL_EVENT_KEY_UP) {
                switch(event.key.key) {
                    case SDLK_F11: {
                        window->toggleFullscreen();
                        break;
                    }
                }
            }
        }

        //pushing new particle into particles
        if (!newParticles.empty()) {
            for (auto& particle : newParticles) {
                particles.push_back(std::move(particle));
            }
            newParticles.clear();
        }

        //pusing new object into object
        if (!newObjects.empty()) {
            for (auto& object : newObjects) {
                objects.push_back(std::move(object));
            }
            newObjects.clear();
        }

        //update objects
        for (auto& object : objects) {
            object->update(window, deltaTime);
        }

        for (auto& particle : particles) {
            particle->update(window, deltaTime);
        }
        
        collisionManager::handleCollision(window, particles);
        
        //cleanup previous frame
        window->refreshRenderer(20, 10, 30, 255);
        
        //draw objects
        for (auto& object : objects) {
            object->draw(window->getRenderer());
        }

        for (auto& particle : particles) {
            particle->draw(window->getRenderer());
        }

        //draw slingshot
        slingshot.draw(window->getRenderer());

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