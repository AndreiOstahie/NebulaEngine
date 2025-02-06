cmake_minimum_required(VERSION 3.20)
project(NebulaEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source and header files
file(GLOB_RECURSE ENGINE_SOURCES "source/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "headers/*.h" "headers/*.hpp")

# Add shader files
file(GLOB_RECURSE SHADER_FILES "${CMAKE_SOURCE_DIR}/Shaders/*.glsl")

# Add executable
add_executable(NebulaEngine ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${SHADER_FILES})

# Group shader files under a "Shaders" folder in the solution
source_group("Shaders" FILES ${SHADER_FILES})

# Set output directories for Visual Studio
set_target_properties(NebulaEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Define paths for dependencies
set(DEPENDENCIES_DIR "${CMAKE_SOURCE_DIR}/libs")
set(GLEW_INCLUDE_DIR "${DEPENDENCIES_DIR}/glew/include")
set(GLEW_LIB_DIR "${DEPENDENCIES_DIR}/glew/lib")
set(GLFW_INCLUDE_DIR "${DEPENDENCIES_DIR}/glfw/include")
set(GLFW_LIB_DIR "${DEPENDENCIES_DIR}/glfw/lib")
set(GLM_INCLUDE_DIR "${DEPENDENCIES_DIR}/glm/include")
set(ASSIMP_INCLUDE_DIR "${DEPENDENCIES_DIR}/assimp/include")
set(ASSIMP_LIB_DIR "${DEPENDENCIES_DIR}/assimp/lib")

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include directories
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${ASSIMP_INCLUDE_DIR}
    "headers"
)

# Link directories
link_directories(
    ${GLFW_LIB_DIR}
    ${GLEW_LIB_DIR}
    ${ASSIMP_LIB_DIR}
)

# Link libraries
target_link_libraries(NebulaEngine
    ${OPENGL_LIBRARIES}
    ${CMAKE_SOURCE_DIR}/libs/glew/lib/glew32.lib
    ${CMAKE_SOURCE_DIR}/libs/glfw/lib/glfw3dll.lib
    ${CMAKE_SOURCE_DIR}/libs/assimp/lib/assimp-vc143-mtd.lib
    
)

# Copy necessary DLLs to the output directory
add_custom_command(TARGET NebulaEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${GLEW_LIB_DIR}/glew32.dll"
    $<TARGET_FILE_DIR:NebulaEngine>
)

add_custom_command(TARGET NebulaEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${GLFW_LIB_DIR}/glfw3.dll"
    $<TARGET_FILE_DIR:NebulaEngine>
)

add_custom_command(TARGET NebulaEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${ASSIMP_LIB_DIR}/assimp-vc143-mtd.dll"
    $<TARGET_FILE_DIR:NebulaEngine>
)

# Copy shader files to the output directory
add_custom_command(TARGET NebulaEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Shaders"
    $<TARGET_FILE_DIR:NebulaEngine>/Shaders
)

# Windows-specific settings
if(WIN32)
    target_link_libraries(NebulaEngine opengl32)  # Explicitly link OpenGL on Windows
endif()

# Set Visual Studio startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT NebulaEngine)


