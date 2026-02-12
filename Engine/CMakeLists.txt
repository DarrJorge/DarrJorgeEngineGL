# general info
cmake_minimum_required(VERSION 3.28.1)

# cpp options
set(CMAKE_CXX_STANDARD 23)

# common options
project(DarrJorgeEngine VERSION 1.0.0)
add_executable(${PROJECT_NAME} Source/main.cpp)


set(ENGINE_SOURCES 
    Source/Core/Engine.h
    Source/Core/Engine.cpp
    Source/Log/Log.h
    Source/Log/Log.cpp
    Source/Core/Utility.h
    Source/Window/GLFW/GLFWWindow.h
    Source/Window/GLFW/GLFWWindow.cpp
    Source/Window/GLFW/GLFWWindowManager.h
    Source/Window/GLFW/GLFWWindowManager.cpp           
)

add_library(${PROJECT_NAME}Lib ${ENGINE_SOURCES})
target_include_directories(${PROJECT_NAME}Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)

# add libs
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PUBLIC spdlog::spdlog)

find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PRIVATE glfw)

# folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Engine)
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER Engine)