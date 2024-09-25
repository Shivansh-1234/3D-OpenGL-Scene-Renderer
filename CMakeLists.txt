cmake_minimum_required(VERSION 3.22)
project(LIFE)

set(CMAKE_CXX_STANDARD 14)

# Set output directories for build files
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add source files (adjust paths if needed)
add_executable(${PROJECT_NAME}
        scripts/main.cpp
        scripts/Graphics/Renderer.cpp
        scripts/Graphics/Renderer.h
        scripts/Graphics/WindowManager.cpp
        scripts/Graphics/WindowManager.h
        scripts/GlobalVariables.h
        scripts/DEPENDENCIES.h
)

# --- PLATFORM DETECTION ---
if(WIN32)
    message(STATUS "Configuring for Windows")

    # --- SDL2 Setup for Windows ---
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
    set(SDL2_PATH "SDL2/x86_64-w64-mingw32")  # Adjust path if necessary

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

elseif(UNIX)
    message(STATUS "Configuring for Linux")

    # --- SDL2 Setup for Linux ---
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

endif()

# --- Glad Setup (Cross-Platform) ---
add_subdirectory(third_party/glad)
include_directories(third_party/glad/include)
target_link_libraries(${PROJECT_NAME} glad)

# --- GLM Setup (Cross-Platform) ---
set(GLM_DIR "${CMAKE_SOURCE_DIR}/third_party/glm")
include_directories(${GLM_DIR})