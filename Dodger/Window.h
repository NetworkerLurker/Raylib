//
// Created by Justice Bole on 10/20/22.
//

#ifndef DODGER_WINDOW_H
#define DODGER_WINDOW_H

#include <raylib.h>
#include <string_view>

class Window {
private:
    int m_width{};
    int m_height{};
    const char* m_title{};

public:
    Window() = default;

    Window(int width, int height, const char* title) :
        m_width{width}, m_height{height}, m_title{title} {
        InitWindow(getWidth(), getHeight(), getTitle());
    }

    ~Window() { CloseWindow(); }

    static void setFps() {
        SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    }

    void initialize() const {
        InitWindow(getWidth(), getHeight(), getTitle());
    };

    [[nodiscard]] int getWidth() const { return m_width; }
    [[nodiscard]] int getHeight() const { return m_height; }
    [[nodiscard]] const char *getTitle() const { return m_title; }
};

#endif //DODGER_WINDOW_H
