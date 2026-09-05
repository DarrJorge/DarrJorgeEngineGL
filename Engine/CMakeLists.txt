# general info
cmake_minimum_required(VERSION 3.28.1)

# cpp options
set(CMAKE_CXX_STANDARD 23)

# common options
project(DarrJorgeEngine VERSION 1.0.0)
add_executable(${PROJECT_NAME} Source/main.cpp)

option(ENGINE_USE_GLFW "Use GLFW as window backend" ON)
set(ENGINE_RENDERER_API "OpenGL" CACHE STRING "Renderer backend")

set_property(CACHE ENGINE_RENDERER_API PROPERTY STRINGS
    OpenGL
    D3D12
    Vulkan
)

# version
configure_file(EngineConfig.h.template ${CMAKE_CURRENT_SOURCE_DIR}/Source/EngineConfig.h)


set(ENGINE_SOURCES 
    Source/Core/Engine.h
    Source/Core/Engine.cpp
    Source/Scene/Camera.h
    Source/Scene/Camera.cpp    
    Source/Core/Utility.h
    Source/Core/MathTypes.h
    Source/Core/MathTypes.cpp      
    Source/Log/Log.h
    Source/Log/Log.cpp    
    Source/Window/IWindow.h
    Source/Window/WindowManager.h
    Source/Window/WindowManager.cpp
    Source/Window/WindowManagerFactory.h
    Source/Window/WindowManagerFactory.cpp
    Source/Window/GLFW/GLFWWindow.h
    Source/Window/GLFW/GLFWWindow.cpp
    Source/Window/GLFW/GLFWWindowManager.h
    Source/Window/GLFW/GLFWWindowManager.cpp 
    Source/Render/Renderer/Renderer.h
    Source/Render/Renderer/Renderer.cpp 
    Source/Render/Renderer/RendererAPI.h
    Source/Render/Renderer/RendererAPIFactory.h
    Source/Render/Renderer/RendererAPIFactory.cpp
    Source/Render/Renderer/RenderCommand.h
    Source/Render/Renderer/RenderCommand.cpp
    Source/Render/RHI/IVertexArray.h
    Source/Render/RHI/RenderDevice.h
    Source/Render/RHI/RenderDeviceFactory.h
    Source/Render/RHI/RenderDeviceFactory.cpp      
    Source/Render/RHI/IBuffer.h
    Source/Render/RHI/IBuffer.cpp
    Source/Render/RHI/IShader.h    
    Source/Render/OpenGL/GLBuffer.h
    Source/Render/OpenGL/GLBuffer.cpp
    Source/Render/OpenGL/GLVertexArray.h
    Source/Render/OpenGL/GLVertexArray.cpp
    Source/Render/OpenGL/GLRenderDevice.h
    Source/Render/OpenGL/GLRenderDevice.cpp
    Source/Render/OpenGL/GLRendererAPI.cpp
    Source/Render/OpenGL/GLRendererAPI.h
    Source/Render/OpenGL/GLShader.cpp
    Source/Render/OpenGL/GLShader.h    
    Source/Event/Event.h
    Source/Event/InputEvent.h
    Source/Resource/Mesh.h
    Source/Resource/Mesh.cpp
    Source/Resource/MeshFactory.h
    Source/Resource/Mesh.cpp 
    Source/Scene/Scene.h
    Source/Scene/Scene.cpp
    Source/Scene/SceneFactory.h
    Source/Scene/SceneFactory.cpp
    Source/Scene/Entity.h
    Source/Scene/Entity.cpp
    Source/Scene/Components/Component.cpp
    Source/Scene/Components/Component.h
    Source/Scene/Components/TransformComponent.h
    Source/Scene/Components/TransformComponent.cpp
    Source/Scene/Components/MeshRendererComponent.cpp
    Source/Scene/Components/MeshRendererComponent.h
    Source/Scene/Components/CameraComponent.h
    Source/Scene/Components/CameraComponent.cpp
    Source/Scene/Components/RotatorComponent.h
    Source/Scene/Components/RotatorComponent.cpp
    Source/Resource/Material.cpp
    Source/Resource/Material.h
    Source/Resource/MeshFactory.h
    Source/Resource/MeshFactory.cpp
)

if (WIN32)
    list(APPEND ENGINE_SOURCES 
        Source/Window/WinAPI/WinAPIWindow.h
        Source/Window/WinAPI/WinAPIWindow.cpp
        Source/Window/WinAPI/WinAPIWindowManager.h
        Source/Window/WinAPI/WinAPIWindowManager.cpp 
    )
endif()


add_library(${PROJECT_NAME}Lib ${ENGINE_SOURCES})
target_include_directories(${PROJECT_NAME}Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

# tests
add_executable(${PROJECT_NAME}TestRunner Tests/LogInputEvent.cpp Tests/LogEvents.cpp)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE ${PROJECT_NAME}Lib)

# ###
# window backend
# ###
if (WIN32)
    if(ENGINE_USE_GLFW)
        target_compile_definitions(${PROJECT_NAME}Lib PRIVATE ENGINE_USE_GLFW)
    else()
        target_compile_definitions(${PROJECT_NAME}Lib PRIVATE ENGINE_USE_WINAPI)
    endif()
endif()

# ###
# renderer backend
# ###
if (ENGINE_RENDERER_API STREQUAL "OpenGL")
    target_compile_definitions(${PROJECT_NAME}Lib PRIVATE ENGINE_RENDERER_OPENGL)

elseif (ENGINE_RENDERER_API STREQUAL "D3D12")
    target_compile_definitions(${PROJECT_NAME}Lib PRIVATE ENGINE_RENDERER_D3D12)

elseif (ENGINE_RENDERER_API STREQUAL "Vulkan")
    target_compile_definitions(${PROJECT_NAME}Lib PRIVATE ENGINE_RENDERER_VULKAN)
else()
    message(FATAL_ERROR "Unknown renderer backend: ${ENGINE_RENDERER_API}")
endif()

# ###
# libs
# ###
find_package(boost REQUIRED)
target_link_libraries(${PROJECT_NAME} boost::boost ${PROJECT_NAME}Lib)

if (MSVC)
    target_compile_options(${PROJECT_NAME}Lib PUBLIC /Zc:preprocessor)
endif()   

# add libs
find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PUBLIC spdlog::spdlog)

find_package(glad REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PRIVATE glad::glad)

find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}Lib PUBLIC glm::glm)

find_package(GTest REQUIRED)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE gtest::gtest)

# folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Engine)
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER Engine)

if (MSVC)
    include(${CMAKE_SOURCE_DIR}/automation/CMake/CMakeHelpers.cmake)
    create_ide_folders(ENGINE_SOURCES)
    setup_precompiled_headers(${PROJECT_NAME}Lib Source/pch.cpp Source/pch.h "${ENGINE_SOURCES}")
else()
     target_precompile_headers(${PROJECT_NAME}Lib PRIVATE  Source/pch.h)
endif()   