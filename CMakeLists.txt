cmake_minimum_required(VERSION 3.15)
project(SolarSystemSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(ALUT CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# Collect all source files
file(GLOB_RECURSE SOURCES
  "GameEngine/*.cpp"
)

# Collect all header files
file(GLOB_RECURSE HEADERS
  "GameEngine/*.h"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/GameEngine
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
  glfw
  GLEW::GLEW
  glm::glm
  OpenAL::OpenAL
  ALUT::ALUT
  assimp::assimp
  OpenGL::GL
  ${CMAKE_DL_LIBS}
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy resources to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/GameEngine/Shaders
  ${CMAKE_BINARY_DIR}/bin/Shaders
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/GameEngine/Textures
  ${CMAKE_BINARY_DIR}/bin/Textures
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/GameEngine/Sounds
  ${CMAKE_BINARY_DIR}/bin/Sounds
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/GameEngine/My_object
  ${CMAKE_BINARY_DIR}/bin/My_object
)
