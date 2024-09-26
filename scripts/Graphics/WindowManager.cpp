#include "WindowManager.h"

#include <glad/glad.h>

void WindowManager::initStuff() {
    input = std::make_shared<Input>();
}

void WindowManager::pollEvents(SDL_Event& event, bool& isRunning) {
    while(SDL_PollEvent(&event)) {
        input->handleEvent(event);

        switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
                if(!SDL_GetRelativeMouseMode()) {
                    isRunning = false;
                } else {
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                }
            break;
        }
    }
}

void WindowManager::createWindow(const std::string& title, const GLint width, const GLint height) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout  << "Failed to INIT SDL VIDEO : " << SDL_GetError() << std::endl;
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

    m_window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,m_width,m_height,SDL_WINDOW_OPENGL);

    if(m_window == nullptr){
        std::cout << "Failed to create window : " << SDL_GetError() << std::endl;
        exit(-1);
    }

    m_context = SDL_GL_CreateContext(m_window);

    if(!m_context)
    {
        std::cout << "Failed to create opengl context : " << SDL_GetError() << std::endl;
        exit(-1);
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    initStuff();


    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, m_width, m_height);



    std::vector<Vertex> vertices = {
        {glm::vec3(-1.f, -1.f, 0.f)},
        {glm::vec3(0.f, -1.f, 1.f)},
        {glm::vec3(1.f, -1.f, 0.f)},
        {glm::vec3(0.f, 1.f, 0.f)}
    };

    std::vector<Vertex> vertices2 = {
        {glm::vec3(-11.f, -1.f, 0.f)},
        {glm::vec3(0.f, -1.f, 1.f)},
        {glm::vec3(11.f, -1.f, 0.f)},
        {glm::vec3(0.f, 1.f, 0.f)}
    };

    std::vector<GLuint> indices = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;


    mesh = std::make_shared<Mesh>(vertices, indices);
    shader = std::make_shared<Shader>(  SRC_PATH "shaders/vertexShader.glsl",
        SRC_PATH "shaders/fragmentShader.glsl");

    float ar = static_cast<float>(m_width) / static_cast<float>(m_height);
    projectionMatrix = glm::perspective(glm::radians(45.0f), ar, 0.1f, 100.0f);
}

void WindowManager::updateWindow()
{
    SDL_Event event;
    while(m_isRunning) {

        input->update();
        pollEvents(event, m_isRunning);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();


        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(0.f, triOffsetX, -2.5f));

        model = glm::rotate(model, curlAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.f));


        shader->setMat4("model", model);
        shader->setMat4("projection", projectionMatrix);


        const Uint8* state = SDL_GetKeyboardState(NULL);

        if(state[SDL_SCANCODE_D])
        {
            triOffsetX += 0.03f;
        }

        if(state[SDL_SCANCODE_A])
        {
            triOffsetX -= 0.03f;
        }

        mesh->render();

        int mouseX, mouseY;
        input->getMousePosCentered(mouseX, mouseY, m_width, m_height);
        std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ")" << std::endl;

        SDL_GL_SwapWindow(m_window);


        curlAngle += 0.4f;

    }
}

void WindowManager::cleanUp()
{
    mesh->cleanup();
    //glDeleteShader(shader->ID);
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


