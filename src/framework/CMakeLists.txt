cmake_minimum_required(VERSION 3.27.0)
project(framework VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC


core/logging.cpp
core/GlslCompiler.cpp
core/VmaUsage.cpp

pv/PvBootstrap.cpp
pv/PvResource.cpp
pv/PvInstance.cpp
pv/PvDebugUtilsMessenger.cpp
pv/PvPhysicalDevice.cpp
pv/PvDevice.cpp
pv/PvSurface.cpp

window/GlfwWindow.cpp
window/WindowBase.cpp
scene/Camera.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
${INCLUDE_DIR}/framework
$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_link_libraries(${PROJECT_NAME} PUBLIC glm spdlog glfw shaderc SPIRV-Tools-opt SPIRV vk-bootstrap::vk-bootstrap volk)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION}) 
include(CPack)