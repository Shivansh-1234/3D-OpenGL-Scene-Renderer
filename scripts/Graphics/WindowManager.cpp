#include "WindowManager.h"

#include <SDL_image.h>
#include <glad/glad.h>
#include <algorithm>

void clampMouseToWindow(SDL_Window* window, SDL_Event* event) {
    int winWidth, winHeight;
    SDL_GetWindowSize(window, &winWidth, &winHeight);

    int x = event->motion.x;
    int y = event->motion.y;

    // Clamp the cursor within the window bounds
    if (x < 0) x = 0;
    if (x > winWidth) x = winWidth;
    if (y < 0) y = 0;
    if (y > winHeight) y = winHeight;

    // Warp the cursor if it's outside the window
    SDL_WarpMouseInWindow(window, x, y);
}

void WindowManager::initStuff() {
    ar = static_cast<float>(m_width) / static_cast<float>(m_height);

    input = std::make_shared<Input>();
    camera = std::make_shared<Camera>();

    brickTexture = std::make_shared<Texture>(RESOURCE_PATH "textures/brick.png");
    floorTexture = std::make_shared<Texture>(RESOURCE_PATH "textures/dirt.png");
    directionalLight= std::make_shared<DirectionalLight>(
        glm::vec3(1.f, 1.f, 1.f),
        glm::vec3(-0.2f, -1.f, -0.3f),
        0.4f,
        0.4f
        );
    material = std::make_shared<Material>(glm::vec3(0.2f, 0.2f, 0.2f), 32.f);
    pointLight = std::make_shared<PointLight>(
        glm::vec3(1.f, 1.f, 1.f),
        0.5f,
        glm::vec3(-4.f, -10.f, 0.f),
        1.f,
        0.045f,
        0.0075f
        );
    spotLight = std::make_shared<SpotLight>(
        glm::vec3(1.f, 1.f, 1.f),
        0.5f,
        camera->position,
        glm::normalize(camera->front),
        glm::cos(glm::radians(12.5f)),
        glm::cos(glm::radians(17.5f))
        );
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
            case SDL_MOUSEMOTION:
                clampMouseToWindow(m_window, &event);
                camera->mouse_callback(static_cast<float> (event.motion.x), static_cast<float> (event.motion.y));
                break;
            case SDL_MOUSEWHEEL:
                camera->scroll_callback(static_cast<float> (event.wheel.y));
        }
    }
}

void WindowManager::processCameraInput() {
    if(input->isKeyDown(SDL_SCANCODE_LSHIFT)){
        camera->movementSpeed = 5.0f;
    }
    if(input->isKeyReleased(SDL_SCANCODE_LSHIFT)){
        camera->movementSpeed = 2.5f;
    }
    if(input->isKeyPressed(SDL_SCANCODE_W)) {
        camera->processKeyboardInputs(CAMERA_MOVEMENT::FORWARD, deltaTime);
    }
    if(input->isKeyPressed(SDL_SCANCODE_S)) {
        camera->processKeyboardInputs(CAMERA_MOVEMENT::BACKWARD, deltaTime);
    }
    if(input->isKeyPressed(SDL_SCANCODE_A)) {
        camera->processKeyboardInputs(CAMERA_MOVEMENT::LEFT, deltaTime);
    }
    if(input->isKeyPressed(SDL_SCANCODE_D)) {
        camera->processKeyboardInputs(CAMERA_MOVEMENT::RIGHT, deltaTime);
    }
}


void WindowManager::createWindow(const std::string& title, const GLint width, const GLint height) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout  << "Failed to INIT SDL VIDEO : " << SDL_GetError() << std::endl;
        exit(-1);
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(-1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);

    m_window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,m_width,m_height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

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
    SDL_GL_SetSwapInterval(1);

    initStuff();


    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, m_width, m_height);

    // Get SDL version
    SDL_version compiled;
    SDL_version linked;

    // Version when SDL was compiled
    SDL_VERSION(&compiled);

    // Version of the SDL library linked at runtime
    SDL_GetVersion(&linked);

    // Output the version
    std::cout << "Compiled against SDL version: "
              << static_cast<int>(compiled.major) << "."
              << static_cast<int>(compiled.minor) << "."
              << static_cast<int>(compiled.patch) << std::endl;

    std::cout << "Linked SDL version: "
              << static_cast<int>(linked.major) << "."
              << static_cast<int>(linked.minor) << "."
              << static_cast<int>(linked.patch) << std::endl;


    //coords for triangle 1 (moved up by 25 floats)
    std::vector<Vertex> t1Vertices = {
        //position                                                      //texCoords                               //normals
        {glm::vec3(-1.f, 2.f, -0.6f)     ,     glm::vec2(0.f ,0.f)     ,       glm::vec3(-0.66666667f,  0.33333333f,  0.66666667f)},
        {glm::vec3(0.f, 2.f, 1.f)        ,     glm::vec2(0.5f, 0.f)    ,       glm::vec3(0.66666667f, 0.33333333f, 0.66666667f)},
        {glm::vec3(1.f, 2.f, -0.6f)      ,     glm::vec2(1.f, 0.f)     ,       glm::vec3(0.f,  0.f, -1.f)},
        {glm::vec3(0.f, 3.f, 0.f)        ,     glm::vec2(0.5f, 1.f)    ,       glm::vec3(0.f, -1.f,  0.f)}
    };

    std::vector<GLuint> t2Indices = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    Mesh::calculateAvgNormals(t1Vertices, t2Indices);

    //coords for the floor
    std::vector<Vertex> floorVertices = {
        //position                                                      //texCoords                               //normals
        {glm::vec3(-10.f, 0.f, -10.f)   ,       glm::vec2(0.f ,0.f)     ,       glm::vec3(0.f, -1.f, 0.f)},
        {glm::vec3(10.f, 0.f, -10.f)    ,       glm::vec2(10.f, 0.f)    ,       glm::vec3(0.f, -1.f, 0.f)},
        {glm::vec3(-10.f, 0.f, 10.f)    ,       glm::vec2(0.f, 10.f)    ,       glm::vec3(0.f, -1.f, 0.f)},
        {glm::vec3(10.f, 0.f, 10.f)     ,       glm::vec2(10.f, 10.f)   ,       glm::vec3(0.f, -1.f, 0.f)}
    };

    std::vector<GLuint> floorIndices = {
        0, 2, 1,
        1, 2, 3
    };

    Mesh::calculateAvgNormals(floorVertices, floorIndices);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;


    mesh = std::make_shared<Mesh>(t1Vertices, t2Indices);
    floorMesh = std::make_shared<Mesh>(floorVertices, floorIndices);
    shader = std::make_shared<Shader>(  SRC_PATH "shaders/vertexShader.glsl",
        SRC_PATH "shaders/fragmentShader.glsl");

    bagpackShader = std::make_shared<Shader>(SRC_PATH "shaders/bagpackVertex.glsl",
        SRC_PATH "shaders/bagpackFragment.glsl");

    bagpackModel = std::make_shared<Model>(RESOURCE_PATH "models/bagpack/backpack.obj");
    helicopterModel = std::make_shared<Model>(RESOURCE_PATH "models/helicopter/Seahawk.obj");
    ironManModel = std::make_shared<Model>(RESOURCE_PATH "models/ironman/IronMan.obj");

    //std::cout << "SDL ERRRR : " << IMG_GetError() << std::endl;

}

void WindowManager::updateWindow()
{
    SDL_Event event;
    while(m_isRunning) {

        float currentFrame = SDL_GetTicks() / 1000.f;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //std::cout << deltaTime << std::endl;

        input->update();

        processCameraInput();


        pollEvents(event, m_isRunning);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader->use();



        brickTexture->activateAndBind(0);


        glm::mat4 model = glm::mat4(1.f);
        //model = glm::translate(model, glm::vec3(0.f, -10.f, 0.f));
        //model = glm::rotate(model, curlAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.f));

        projectionMatrix = glm::perspective(glm::radians(camera->zoom), ar, 0.1f, 100.0f);


        viewMatrix = camera->getViewMatrix();

        spotLight->setPosition(camera->position);
        spotLight->setDirection(camera->front);


        shader->setMat4("projection", projectionMatrix);
        shader->setMat4("view", viewMatrix);
        shader->setMat4("model", model);
        shader->setVec3("viewPos", camera->position);
        shader->setVec3("ironManColor", glm::vec3(1.f));


        directionalLight->setUniforms(shader, "directionalLight");
        material->setUniforms(shader, "material");
        pointLight->setUniforms(shader, "pointLight[0]");
        spotLight->setUniforms(shader, "spotLight");

        mesh->render(shader);
        brickTexture->unbind();

        floorTexture->activateAndBind(0);
        floorMesh->render(shader);

        floorTexture->unbind();


        //bagpackShader->use();

        model = glm::translate(model, glm::vec3(2.f, 2.f, 2.f));
        model = glm::scale(model, glm::vec3(0.3f));

        shader->setMat4("model", model);


        //bagpackShader->setMat4("projection", projectionMatrix);
        //bagpackShader->setMat4("view", viewMatrix);
        //bagpackShader->setMat4("model", model);

        //model = glm::translate(model, glm::vec3(3.f, 3.f, 3.f));


        //glGetUniformLocation(bagpackShader->ID, "FragColor"


        bagpackModel->render(shader);

        heliRotationAngle += 0.2f;
        if(heliRotationAngle > 360.f) { heliRotationAngle = 0.f; }

        model = glm::translate(model, glm::vec3(-3.f, 3.f, -3.f));
        model = glm::rotate(model, glm::radians(heliRotationAngle), glm::vec3(0.f, 1.f, 0.f));
        model = glm::translate(model, glm::vec3(-30.f, 2.f, 0.f));
        model = glm::rotate(model, glm::radians(glm::radians(-90.f)), glm::vec3(1.f, 0.f, 0.f));
        model = glm::scale(model, glm::vec3(0.05f));

        shader->setMat4("model", model);

        helicopterModel->render(shader);


        model = glm::scale(model, glm::vec3(0.5f));
        model = glm::translate(model, glm::vec3(0.f, 75.f, 0.f));
        shader->setMat4("model", model);

        shader->setVec3("ironManColor", glm::vec3(1.f, 0.f, 0.f));


        ironManModel->render(shader);

        SDL_GL_SwapWindow(m_window);

        curlAngle += 0.4f;

    }
}

void WindowManager::cleanUp()
{
    mesh->cleanup();
    floorMesh->cleanup();
    glDeleteShader(shader->ID);
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}



