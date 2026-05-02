#include <iostream>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

int main(int argc, char* argv[]) 
{
    int w = 1280;
    int h = 960;

    SDL_Window *mainWindow;
    SDL_Init(SDL_INIT_VIDEO);

    mainWindow = SDL_CreateWindow("Title", w, h, SDL_WINDOW_RESIZABLE);

    if (mainWindow == nullptr) 
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "failed creating window", nullptr);
        return 1;
    }

    bool running = true;

    while (running) 
    {
        SDL_Event event;

        while (SDL_PollEvent(&event)) 
        {
            switch(event.type) 
            {
                case SDL_EVENT_QUIT: 
                {
                    running = false;
                    break;
                }
            }
        }
    }

    SDL_DestroyWindow(mainWindow);

    SDL_Quit();

    return 0;
}