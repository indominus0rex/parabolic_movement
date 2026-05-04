#pragma once

#include <SDL3/SDL.h>
#include <string>

class Window {
private:

    SDL_Window* window;
    SDL_Renderer* renderer;

    int windowH;
    int windowW;
    int windowLogH;
    int windowLogW;

    bool isFullscreen;

public:
    
    Window(const std::string& windowTitle, int windowWidth, int windowHeight, int logW, int logH, SDL_WindowFlags windowFlag);

    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    int Height() const;
    int Width() const;
    int logHeight() const;
    int logWidth() const;
    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;
    
    void updateSize(int w, int h);
    void setTitle(const std::string& newTitle);
    void toggleFullscreen();
    void refreshRenderer(Uint8 r, Uint8 g, Uint8 b, Uint8 a); 
    void updateFrame();
};