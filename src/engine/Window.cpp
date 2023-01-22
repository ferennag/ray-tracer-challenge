#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include "Window.h"
#include "../debug/Timer.h"

Window::Window(std::string_view title, int width, int height, std::unique_ptr<Renderer> renderer) {
    m_width = width;
    m_height = height;
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cerr << "Unable to init SDL: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    m_window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
                                height, 0);

    m_sdlRenderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    m_texture = SDL_CreateTexture(m_sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    m_renderer = std::move(renderer);
}

Window::~Window() {
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_sdlRenderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::show() {
    Timer timer;
    auto renderFuture = requestRender();

    while (!m_shouldClose) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    m_shouldClose = true;
                    break;
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            m_shouldClose = true;
                            m_renderingThread.request_stop();
                            break;
                    }
                }
            }
        }

        // Whenever the render is ready, copy it to the texture, and request a new render
        if (renderFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            timer.reportElapsed("Frame render");
            updateTexture();
            timer.reportElapsed("Texture update");
            renderFuture = requestRender();
        } else {
            updateTexture();
        }

        SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 0);
        SDL_RenderClear(m_sdlRenderer);
        SDL_RenderCopy(m_sdlRenderer, m_texture, nullptr, nullptr);
        SDL_RenderPresent(m_sdlRenderer);
        SDL_Delay(1000 / 60);
    }
}

void Window::render(std::promise<bool> promise) {
    m_renderer->render();
    // Set the value to true, notifying the main thread that the render is complete
    promise.set_value(true);
}

std::future<bool> Window::requestRender() {
    std::promise<bool> renderCompletePromise;
    auto renderFuture { renderCompletePromise.get_future() };
    m_renderingThread = std::jthread { &Window::render, this, std::move(renderCompletePromise) };
    return renderFuture;
}

void Window::updateTexture() {
    int pitch;
    Uint32 *pixels = nullptr;

    SDL_LockTexture(m_texture, nullptr, (void **) &pixels, &pitch);
    auto &buffer = m_renderer->getBuffer();

    for (int row = 0; row < m_height; ++row) {
        for (int col = 0; col < m_width; ++col) {
            pixels[row * m_width + col] = buffer[row][col].getUint32();
        }
    }

    SDL_UnlockTexture(m_texture);
}
