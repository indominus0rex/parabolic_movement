#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <fmt/core.h>

int main(int argc, char* argv[]) {

    int windowW = 1280;
    int windowH = 960;
    int logW = 640;
    int logH = 360;
    
    SDL_Window* mainWindow;
    mainWindow = SDL_CreateWindow("Title", windowW, windowH, SDL_WINDOW_RESIZABLE);
    
    SDL_Renderer* mainRenderer;
    mainRenderer = SDL_CreateRenderer(mainWindow, nullptr);
    SDL_SetRenderLogicalPresentation(mainRenderer, logW, logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    SDL_Init(SDL_INIT_VIDEO);

    bool running = true;
    float prevTime = SDL_GetTicks() / 1000.0f;

    while (running) {
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
        
        //set background color
        SDL_SetRenderDrawColor(mainRenderer, 20, 10, 30, 255);
        SDL_RenderClear(mainRenderer);
        
        //display time elapse
        SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

        float currentTime = SDL_GetTicks() / 1000.0f;
        float deltaTime = (currentTime - prevTime)/ 1000.0f;
        
        std::string debugText = fmt::format("Current Time = {:.3f}s", currentTime);
        SDL_RenderDebugText(mainRenderer, 10, 10, debugText.c_str());


        //load renderer
        SDL_RenderPresent(mainRenderer);
    }

    SDL_DestroyWindow(mainWindow);

    SDL_Quit();

    return 0;
}