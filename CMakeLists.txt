cmake_minimum_required(VERSION 3.10)
project(AtomEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

# Incluir glm headers
include_directories(include ${GLFW_INCLUDE_DIRS} /usr/include/glm)

set(SOURCES
    src/main.cpp
    src/Core/Atom.cpp
    src/Core/Atom2D.cpp
    src/Core/Game.cpp
    src/Core/TextureManager.cpp
    src/Graphics/Window.cpp
    src/Graphics/Texture.cpp
    src/Graphics/Sprite.cpp
    src/Graphics/Shader.cpp
    src/Utils/AtomError.cpp
    src/Utils/Logger.cpp
    src/Utils/Timer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} OpenGL::GL GLEW::GLEW ${GLFW_LIBRARIES})
