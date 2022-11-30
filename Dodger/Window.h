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
    Window();

    Window(int width, int height, const char* title);

    ~Window();

    static void setDefaultFps();

    void initialize() const;

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    [[nodiscard]] const char* getTitle() const;
};

#endif //DODGER_WINDOW_H
