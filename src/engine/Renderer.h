#ifndef RAY_TRACER_CHALLENGE_RENDERER_H
#define RAY_TRACER_CHALLENGE_RENDERER_H

#include <cstdint>
#include <vector>
#include "Color.h"

class Renderer {
public:
    Renderer(int width, int height);
    virtual ~Renderer() = default;

    virtual void render() = 0;

    void setClearColor(const Color &color);
    void clear();
    std::vector<std::vector<Color>> &getBuffer();
protected:
    int m_width, m_height;
    Color m_clearColor;
    std::vector<std::vector<Color>> m_buffer;
};


#endif //RAY_TRACER_CHALLENGE_RENDERER_H
