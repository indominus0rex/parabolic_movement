#include <iostream>

#include "window.hpp"

Window::Window(const std::string& windowTitle, int windowWidth, int windowHeight, int logW, int logH, SDL_WindowFlags windowFlag)
    : windowH(windowHeight), windowW(windowWidth), windowLogW(logW), windowLogH(logH), isFullscreen(false) { 
    
    window = SDL_CreateWindow(windowTitle.c_str(), windowWidth, windowHeight, windowFlag);     
    if (!window) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "failed creating window", nullptr);
        
    renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderLogicalPresentation(renderer, logW, logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    if (!renderer) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "failed creating renderer", nullptr);    
}

Window::~Window() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
}

int Window::Height() const { return windowH; }
int Window::Width() const { return windowW; }
int Window::logHeight() const { return windowLogH; }
int Window::logWidth() const { return windowLogW; }
SDL_Window* Window::getWindow() const { return window; }
SDL_Renderer* Window::getRenderer() const { return renderer; }

void Window::updateSize(int w, int h) { windowH = h; windowW = w; }
void Window::setTitle(const std::string& newTitle) { SDL_SetWindowTitle(window, newTitle.c_str()); }
void Window::toggleFullscreen() {
    if (isFullscreen) {
        SDL_SetWindowFullscreen(window, false);
        isFullscreen = false;
    }
    else {
        SDL_SetWindowFullscreen(window, true);
        isFullscreen = true;
    }
}
void Window::refreshRenderer(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //background color
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_FRect activeArea = { 0, 0, (float) windowLogW, (float) windowLogH };
    SDL_RenderFillRect(renderer, &activeArea);
} 

void Window::updateFrame() { SDL_RenderPresent(renderer); }
