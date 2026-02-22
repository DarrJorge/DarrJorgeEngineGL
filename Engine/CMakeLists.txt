# general info
cmake_minimum_required(VERSION 3.28.1)

# cpp options
set(CMAKE_CXX_STANDARD 23)

# common options
project(DarrJorgeEngine VERSION 1.0.0)
add_executable(${PROJECT_NAME} Source/main.cpp)

# version
configure_file(EngineConfig.h.template ${CMAKE_CURRENT_SOURCE_DIR}/Source/EngineConfig.h)


set(ENGINE_SOURCES 
    Source/Core/Engine.h
    Source/Core/Engine.cpp
    Source/Core/Utility.h
    Source/Core/MathTypes.h
    Source/Core/MathTypes.cpp    
    Source/Log/Log.h
    Source/Log/Log.cpp    
    Source/Window/GLFW/GLFWWindow.h
    Source/Window/GLFW/GLFWWindow.cpp
    Source/Window/GLFW/GLFWWindowManager.h
    Source/Window/GLFW/GLFWWindowManager.cpp 
    Source/Render/Renderer/Renderer.h
    Source/Render/Renderer/Renderer.cpp 
    Source/Render/Renderer/RendererAPI.h
    Source/Render/Renderer/RendererAPI.cpp
    Source/Render/Renderer/RenderCommand.h
    Source/Render/Renderer/RenderCommand.cpp
    Source/Render/RHI/VertexArray.h
    Source/Render/RHI/RenderDevice.h
    Source/Render/RHI/Shader.h     
    Source/Render/RHI/Shader.cpp         
    Source/Render/RHI/IBuffer.h
    Source/Render/RHI/IBuffer.cpp    
    Source/Render/OpenGL/GLBuffer.h
    Source/Render/OpenGL/GLBuffer.cpp
    Source/Render/OpenGL/GLVertexArray.h
    Source/Render/OpenGL/GLVertexArray.cpp
    Source/Render/OpenGL/GLRenderDevice.h
    Source/Render/OpenGL/GLRenderDevice.cpp
    Source/Render/OpenGL/GLRendererAPI.cpp
    Source/Render/OpenGL/GLRendererAPI.h

)

add_library(${PROJECT_NAME}Lib ${ENGINE_SOURCES})
target_include_directories(${PROJECT_NAME}Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)

# add libs
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PUBLIC spdlog::spdlog)

find_package(glad REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PRIVATE glad::glad)

find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PRIVATE glfw)

find_package(glm REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PRIVATE glm::glm)

# folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Engine)
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER Engine)