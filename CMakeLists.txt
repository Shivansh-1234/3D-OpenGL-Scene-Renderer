cmake_minimum_required(VERSION 3.22)
project(LIFE)

set(CMAKE_CXX_STANDARD 14)

# Add source files (adjust paths if needed)
add_executable(${PROJECT_NAME}
        scripts/main.cpp
        scripts/Graphics/Renderer.cpp
        scripts/Graphics/Renderer.h
        scripts/Graphics/WindowManager.cpp
        scripts/Graphics/WindowManager.h
        scripts/GlobalVariables.h
        scripts/DEPENDENCIES.h
        scripts/Graphics/Mesh.cpp
        scripts/Graphics/Mesh.h
        scripts/Graphics/Shader.cpp
        scripts/Graphics/Shader.h
        scripts/core/Input.cpp
        scripts/core/Input.h
        scripts/Graphics/Camera.cpp
        scripts/Graphics/Camera.h
        scripts/Graphics/Texture.cpp
        scripts/Graphics/Texture.h
        scripts/Graphics/Lighting/Light.cpp
        scripts/Graphics/Lighting/Light.h
        scripts/Graphics/Lighting/DirectionalLight.cpp
        scripts/Graphics/Lighting/DirectionalLight.h
        scripts/Graphics/Lighting/Material.cpp
        scripts/Graphics/Lighting/Material.h
)

# --- PLATFORM DETECTION ---
if(WIN32)
    message(STATUS "Configuring for Windows")

    # --- SDL2 Setup for Windows ---
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
    set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
    set(SDL2_IMAGE_PATH "third_party/sdl_image/x86_64-w64-mingw32")

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})

    # Find SDL2_image
    find_package(SDL2_image REQUIRED)
    include_directories(${SDL2_IMAGE_INCLUDE_DIR})

    # Link SDL2 and SDL2_image
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

elseif(UNIX)
    message(STATUS "Configuring for Linux")

    # --- SDL2 Setup for Linux ---
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    # Find SDL2_image
    find_package(SDL2_image REQUIRED)
    include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

    # Link SDL2 and SDL2_image
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_image::SDL2_image)

endif()

# --- RESOURCE_PATH Setup ---
set(RESOURCE_PATH "${CMAKE_SOURCE_DIR}/resources/")
add_definitions(-DRESOURCE_PATH=\"${RESOURCE_PATH}\")

# --- SRC_PATH Setup ---
set(SRC_PATH "${CMAKE_SOURCE_DIR}/scripts/")
add_definitions(-DSRC_PATH=\"${SRC_PATH}\")

# --- Glad Setup (Cross-Platform) ---
add_subdirectory(third_party/glad)
include_directories(third_party/glad/include)
target_link_libraries(${PROJECT_NAME} glad)

# --- GLM Setup (Cross-Platform) ---
set(GLM_DIR "${CMAKE_SOURCE_DIR}/third_party/glm")
include_directories(${GLM_DIR})