//
// Created by Justice Bole on 11/30/22.
//

#include "Window.h"

Window::Window() = default;

Window::Window(int width, int height, const char* title) :
        m_width{width}, m_height{height}, m_title{title} {
}

Window::~Window() { CloseWindow(); }

void Window::setDefaultFps() {
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
}

void Window::initialize() const {
    InitWindow(getWidth(), getHeight(), getTitle());
};

int Window::getWidth() const { return m_width; }
int Window::getHeight() const { return m_height; }
int Window::getHalfWidth() const { return m_width * .5f; }
int Window::getHalfHeight() const { return m_height * .5f; }
const char* Window::getTitle() const { return m_title; }