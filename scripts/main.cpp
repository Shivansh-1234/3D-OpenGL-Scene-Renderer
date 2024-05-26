#include <iostream>
#include <SDL.h>
#include <glad/glad.h>

void pollEvents(SDL_Event& event, bool& isRunning) {
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    isRunning = false;
                break;
        }
    }
}

int main(int argc, char* args []) {

    const GLint WIDTH = 1920, HEIGHT = 1080;
    bool isRunning = true;

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout  << "Failed to INIT SDL VIDEO : " << SDL_GetError() << std::endl;
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

    SDL_Window* window = SDL_CreateWindow("test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    if(window == nullptr){
         std::cout << "Failed to create window : " << SDL_GetError() << std::endl;
        exit(-1);
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

    if(!context)
    {
        std::cout << "Failed to create opengl context : " << SDL_GetError() << std::endl;
        exit(-1);
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    // Main loop
    SDL_Event event;
    while(isRunning) {

        pollEvents(event, isRunning);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);


    }

    // Clean up
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
