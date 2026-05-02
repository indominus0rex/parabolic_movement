#pragma once

#include <SDL3/SDL.h>
#include <string>

class Window {
private:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    int windowH;
    int windowW;
    int windowLogH;
    int windowLogW;

public:
    
    Window(const std::string& windowTitle, int windowWidth, int windowHeight, int logW, int logH, SDL_WindowFlags windowFlag)
        : windowH(windowHeight), windowW(windowWidth) { 
        
        window = SDL_CreateWindow(windowTitle.c_str(), windowWidth, windowHeight, windowFlag);     
        if (!window) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "failed creating window", nullptr);
            
        renderer = SDL_CreateRenderer(window, nullptr);
        SDL_SetRenderLogicalPresentation(renderer, logW, logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);
        if (!renderer) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "failed creating renderer", nullptr);    
    }

    ~Window() {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    int Height() const { return windowH; }
    int Width() const { return windowW; }
    SDL_Window* getWindow() const { return window; }
    SDL_Renderer* getRenderer() const { return renderer; }
    
    void setSize(int w, int h) { windowH = h; windowW = w; }
    
    void setTitle(const std::string& newTitle) { SDL_SetWindowTitle(window, newTitle.c_str()); }

    void toggleFullscreen() {
        int flag = SDL_GetWindowFlags(window);
        if (flag && SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(window, false);
        else SDL_SetWindowFullscreen(window, true);
    }

    void cleanup(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderClear(renderer);
    } 

    void updateFrame() { SDL_RenderPresent(renderer); }
};