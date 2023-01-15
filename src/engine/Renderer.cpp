#include "Renderer.h"

Renderer::Renderer(int width, int height) {
    m_width = width;
    m_height = height;

    for (int row = 0; row < height; ++row) {
        std::vector<Color> rowColors;
        for (int col = 0; col < width; ++col) {
            rowColors.emplace_back();
        }
        m_buffer.push_back(rowColors);
    }
}

std::vector<std::vector<Color>> &Renderer::getBuffer() {
    return m_buffer;
}

void Renderer::clear() {
    for (auto &row: m_buffer) {
        for (auto &color: row) {
            color.copy(m_clearColor);
        }
    }
}

void Renderer::setClearColor(const Color &color) {
    m_clearColor = color;
}
