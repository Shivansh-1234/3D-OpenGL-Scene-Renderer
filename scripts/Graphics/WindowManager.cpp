//
// Created by karti on 26-05-2024.
//

#include "WindowManager.h"

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

void WindowManager::createWindow(const std::string& title, const GLint width, const GLint height)
{
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


    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, m_width, m_height);

    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    float vertices[] = {
        -1.f, -1.f, 0.f,
         0.f, -1.f, 1.f,
         1.f, -1.f, 0.f,
         0.f, 1.f, 0.f
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 vCol;\n"
    "uniform mat4 model; \n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * model * vec4(aPos, 1.0);\n"
    "   vCol = vec4(clamp(aPos, 0.f, 1.f), 1.f);\n"
    "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    const char* fragmentShaderSource = "#version 330 core\n"
    "in vec4 vCol;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vCol;\n"
    "}\n\0";



    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    uniformModel = glGetUniformLocation(shaderProgram, "model");
    uniformProjection = glGetUniformLocation(shaderProgram, "projection");

    float ar = static_cast<float>(m_width) / static_cast<float>(m_height);
    projectionMatrix = glm::perspective(glm::radians(45.0f), ar, 0.1f, 100.0f);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void WindowManager::updateWindow()
{
    SDL_Event event;
    while(m_isRunning) {
        pollEvents(event, m_isRunning);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);


        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(0.f, triOffsetX, -2.5f));

        model = glm::rotate(model, curlAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.f));


        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


        const Uint8* state = SDL_GetKeyboardState(NULL);

        if(state[SDL_SCANCODE_D])
        {
            triOffsetX += 0.03f;
        }

        if(state[SDL_SCANCODE_A])
        {
            triOffsetX -= 0.03f;
        }

        glDrawElements(GL_TRIANGLES, 12 ,GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(m_window);

        std::cout << triOffsetX << std::endl;

        curlAngle += 0.4f;

    }
}

void WindowManager::cleanUp()
{
    glDeleteShader(shaderProgram);
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


