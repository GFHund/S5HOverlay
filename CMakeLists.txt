cmake_minimum_required(VERSION 3.0.0)
project(S5HOverlay VERSION 0.1.0)

find_package(Boost REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_libraries(${Boost_LIBRARIES})
    message("Boost found\n")
endif()

find_package(Threads REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("vendor/glfw-3.3.2")

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    message(${GLEW_INCLUDE_DIR})
    # message(${GLEW_INCLUDE_DIRS})
    include_directories(${GLEW_INCLUDE_DIR})
    link_libraries(${GLEW_LIBRARIES})
    message(${GLEW_LIBRARIES})
    message("GLEW found\n")
endif()

find_package(OpenGL REQUIRED)

find_package(FreeType REQUIRED)
if (FREETYPE_FOUND)
    include_directories(${FREETYPE_INCLUDE_DIRS})
endif()

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCES src/main.cpp
    src/Overlay.cpp
    src/Shader.cpp
    src/Image.cpp
    src/Exceptions/normalizeZeroVectorException.cpp
    src/renderer/Renderer.cpp
    src/renderer/RenderFont.cpp
    src/objects/Rectangle.cpp
    src/objects/Ring.cpp
    src/math/vector.cpp
    src/math/matrix.cpp
    src/math/quaternion.cpp
    src/stateMachine/StateMachine.cpp
    src/stateMachine/LastLapTimeState.cpp)

add_executable(S5HOverlay ${SOURCES})

if(MINGW)
    message("FOUND MINGW \n")
    target_link_libraries(S5HOverlay ws2_32 ${CMAKE_THREAD_LIBS_INIT} glfw OpenGL::GL ${FREETYPE_LIBRARIES})
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
