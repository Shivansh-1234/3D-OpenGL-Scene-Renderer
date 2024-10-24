#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "../DEPENDENCIES.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../core/Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "../core/Input.h"
#include "Lighting/DirectionalLight.h"
#include "Lighting/Material.h"
#include "Lighting/PointLight.h"
#include "Lighting/SpotLight.h"

class WindowManager {

public:
    static WindowManager& getInstance() {
        static WindowManager instance;
        return instance;
    }

    void createWindow(const std::string& title, const GLint width, const GLint height);
    void updateWindow();
    void cleanUp();
private:
    WindowManager() : m_width(2560), m_height(1440), m_window(nullptr), m_context(nullptr) {}
    ~WindowManager() = default;
    WindowManager(const WindowManager&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    void pollEvents(SDL_Event& event, bool& isRunning);
    void initStuff();
    void processCameraInput();

    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context = nullptr;
    const GLint m_width = 2560;
    const GLint m_height = 1440;
    bool m_isRunning = true;
    float deltaTime = 0.f;
    float lastFrame = 0.f;

    unsigned int  shaderProgram;
    unsigned int uniformModel;
    unsigned int uniformProjection;
    float triOffsetX = 0.f;
    const float toRadians = 3.14159265f / 180.f;
    float curlAngle = 0.f;
    float ar;
    GLfloat heliRotationAngle = 0.f;
    glm::mat4 projectionMatrix = glm::mat4(1.f);
    glm::mat4 viewMatrix = glm::mat4(1.f);

    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Mesh> mesh2;
    std::shared_ptr<Mesh> floorMesh;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Shader> bagpackShader;
    std::shared_ptr<Input> input;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Texture> brickTexture;
    std::shared_ptr<Texture> floorTexture;
    std::shared_ptr<DirectionalLight> directionalLight;
    std::shared_ptr<PointLight> pointLight;
    std::shared_ptr<SpotLight> spotLight;
    std::shared_ptr<Material> material;
    std::shared_ptr<Model> bagpackModel;
    std::shared_ptr<Model> helicopterModel;
    std::shared_ptr<Model> ironManModel;
};



#endif //WINDOWMANAGER_H
