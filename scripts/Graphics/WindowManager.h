//
// Created by karti on 26-05-2024.
//

#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "../DEPENDENCIES.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class WindowManager {

public:
    static WindowManager& getInstance() {
        static WindowManager instance;
        return instance;
    }

    void createWindow(const std::string& title, const GLint width, const GLint height);
    void updateWindow();
    void cleanUp();

    SDL_Window* m_window1() const
    {
        return m_window;
    }

    GLint m_width1() const
    {
        return m_width;
    }

    GLint m_height1() const
    {
        return m_height;
    }

    bool m_is_running() const
    {
        return m_isRunning;
    }

private:
    WindowManager() : m_width(1920), m_height(1080), m_window(nullptr), m_context(nullptr) {}
    ~WindowManager() = default;
    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context = nullptr;
    const GLint m_width = 1920;
    const GLint m_height = 1080;
    bool m_isRunning = true;

    unsigned int  shaderProgram;
    unsigned int uniformModel;
    float triOffsetX = 0.f;

};



#endif //WINDOWMANAGER_H
