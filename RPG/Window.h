//
// Created by Justice Bole on 10/7/22.
//

#ifndef RPG_WINDOW_H
#define RPG_WINDOW_H

#include <raylib.h>
#include <string_view>


class Window
{
private:
    int m_width{};
    int m_height{};
    const char* m_title{};
    int m_fps{};


public:
    explicit Window(int w = 800, int h = 450, const char* title = "Default", int fps = 60) :
    m_width{w}, m_height{h}, m_title{title}, m_fps{fps}
    {
        InitWindow(m_width, m_height, m_title);
        SetTargetFPS(m_fps);
    }

    ~Window() noexcept{ CloseWindow(); }

    [[nodiscard]] int getWidth() const { return m_width; }
    [[nodiscard]] int getHeight() const { return m_height; }

};

#endif //RPG_WINDOW_H
