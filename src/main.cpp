#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <string>
#include <fmt/core.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

#include "drawObject.hpp"
#include "button.hpp"
#include "slingshot.hpp"
#include "interaction.hpp"
#include "object.hpp"
#include "window.hpp"
#include "collisionManager.hpp"

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    Window* window = new Window("Title", 1280, 720, 640, 360, SDL_WINDOW_RESIZABLE);

    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Interaction>> interactables;
    std::vector<std::unique_ptr<Interaction>> mechanics;

    //add slingshot
    mechanics.push_back(std::make_unique<Slingshot>(InteractableType::SLINGSHOT));

    //add drawobject
    mechanics.push_back(std::make_unique<DrawObject>(InteractableType::DRAWOBJECT));

    //add inputmode button
    ButtonConfig inputModeButtonConfig;
    inputModeButtonConfig.position = glm::vec2(50, 20);
    inputModeButtonConfig.size = glm::vec2(50, 20);
    inputModeButtonConfig.color = SDL_Color{150, 150, 150, 255};
    inputModeButtonConfig.interactabletype = InteractableType::BUTTON;
    inputModeButtonConfig.onClick = []() {
        std::cout << "Hello World\n";
    };
    interactables.push_back(std::make_unique<Button>(inputModeButtonConfig));

    bool mouseOverInteractables = false;
    bool running = true;
    float prevTime = SDL_GetTicks() / 1000.0f;
    
    while (running) {

        float currentTime = SDL_GetTicks() / 1000.0f;
        float deltaTime = currentTime - prevTime;
        prevTime = currentTime;
        
        std::vector<std::unique_ptr<Object>> newObjects;

        SDL_Event event;
        
        while (SDL_PollEvent(&event)) {

            for (auto& interactable : interactables) {
                interactable->handleEvents(window, event, newObjects);

                if (interactable->getIsHovered()) {
                    mouseOverInteractables = true;
                }
            }

            if (!mouseOverInteractables) {
                for (auto& mechanic : mechanics) {
                    mechanic->handleEvents(window, event, objects);
                }
            }

            mouseOverInteractables = false;

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

        //update interactables
        for (auto& interactable : interactables) {
            interactable->update(window, deltaTime);
        }

        //handle object collisions
        collisionManager::handleCollision(window, objects);
        
        //cleanup previous frame
        window->refreshRenderer(0, 0, 0, 255);

        //draw objects
        for (auto& object : objects) {
            object->draw(window->getRenderer());
        }

        //draw interactables
        for (auto& interactable : interactables) {
            interactable->draw(window->getRenderer());
        }

        //draw mechanics
        for (auto& mechanic : mechanics) {
            mechanic->draw(window->getRenderer());

            if (mechanic->getType() == InteractableType::DRAWOBJECT) {
                auto* drawObject = static_cast<DrawObject*>(mechanic.get());

                SDL_RenderDebugText(window->getRenderer(), 100, 15, fmt::format("CURRENT INPUTMODE : {}", drawObject->getInputModeText()).c_str());
            }
        }

        // // display time elapse
        // SDL_SetRenderDrawColor(window->getRenderer(), 255, 255, 255, 255);
        // SDL_RenderDebugText(window->getRenderer(), 10, 10, fmt::format("Current Time = {:.3f}s", currentTime).c_str());
        
        //update frame
        window->updateFrame();
    }

    delete window;
    
    SDL_Quit();

    return 0;
}