cmake_minimum_required(VERSION 3.22)
project(LIFE)

set(CMAKE_CXX_STANDARD 14)

# Must set the path to the main.cpp, for example: scripts/main.cpp if it is inside a folder
add_executable(${PROJECT_NAME} scripts/main.cpp
        scripts/Graphics/Renderer.cpp
        scripts/Graphics/Renderer.h
        scripts/Graphics/WindowManager.cpp
        scripts/Graphics/WindowManager.h
        scripts/GlobalVariables.h
        scripts/DEPENDENCIES.h)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

# --- Glad SETUP ---
add_subdirectory(third_party/glad)
include_directories(third_party/glad/include)
target_link_libraries(${PROJECT_NAME} glad)

# --- GLM SETUP ---
set(GLM_DIR "${CMAKE_SOURCE_DIR}/third_party/glm")
include_directories(${GLM_DIR})