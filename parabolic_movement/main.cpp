#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <fmt/core.h>

#include "window.h"

struct object {
    int x;
    int y;
    float gravity;
    bool active;

    object(int x, int y) : x(x), y(y), gravity(9.8f), active(true) {}
};

int main(int argc, char* argv[]) {

    int windowW = 1280;
    int windowH = 960;
    int logW = 640;
    int logH = 360;
    
    SDL_Init(SDL_INIT_VIDEO);
    Window* window = new Window("Title", windowW, windowH, SDL_WINDOW_RESIZABLE);
    
    bool running = true;
    float prevTime = SDL_GetTicks() / 1000.0f;
    
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

                }
            }
        }
        
        //cleanup previous frame
        window->cleanup(20, 10, 30);

        //display time elapse
        SDL_SetRenderDrawColor(window->getRenderer(), 255, 255, 255, 255);

        
        std::string debugText = fmt::format("Current Time = {:.3f}s", currentTime);
        SDL_RenderDebugText(window->getRenderer(), 10, 10, debugText.c_str());


        //update frame
        window->updateFrame();
    }

    delete window;
    
    SDL_Quit();

    return 0;
}