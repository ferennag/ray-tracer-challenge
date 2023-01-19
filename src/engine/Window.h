#ifndef RAY_TRACER_CHALLENGE_WINDOW_H
#define RAY_TRACER_CHALLENGE_WINDOW_H

#include <memory>
#include <future>
#include <thread>
#include <string_view>
#include <SDL.h>
#include "Renderer.h"

class Window {
public:
    Window(std::string_view title, int width, int height, std::unique_ptr<Renderer> renderer);
    virtual ~Window();

    void show();
protected:
    bool m_shouldClose { false };
    int m_width, m_height;
    std::unique_ptr<Renderer> m_renderer;
    SDL_Window *m_window;
    SDL_Renderer *m_sdlRenderer;
    SDL_Texture *m_texture;
    std::jthread m_renderingThread;

    std::future<bool> requestRender();
    void render(std::promise<bool> promise);
    void updateTexture();
};


#endif //RAY_TRACER_CHALLENGE_WINDOW_H
