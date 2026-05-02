#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

int main(int argc, char* argv[]) 
{
    int w = 1280;
    int h = 960;
    
    SDL_Window* mainWindow;
    mainWindow = SDL_CreateWindow("Title", w, h, SDL_WINDOW_RESIZABLE);
    
    SDL_Renderer* mainRenderer;
    mainRenderer = SDL_CreateRenderer(mainWindow, nullptr);
    
    SDL_Init(SDL_INIT_VIDEO);

    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_EVENT_QUIT: {
                    running = false;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
        SDL_RenderClear(mainRenderer);

        SDL_RenderPresent(mainRenderer);
    }

    SDL_DestroyWindow(mainWindow);

    SDL_Quit();

    return 0;
}