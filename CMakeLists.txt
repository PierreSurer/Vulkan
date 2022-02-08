cmake_minimum_required(VERSION 3.10)

foreach(path ${CMAKE_PREFIX_PATH})
  message("Path: " ${path})
endforeach(path)

# set the project name
set(PROJECT_NAME "Vulkan")
project(${PROJECT_NAME} VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# install glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/Libraries/glfw-3.3.6)
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ${glfw3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${glfw3_LIBRARIES})

# install glm
set(GLM_INCLUDE_DIR  OFF CACHE BOOL "" FORCE)
set(GLM_LIBRARY_DIR  OFF CACHE BOOL "" FORCE)

find_package(GLM REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GLFW_LIBRARIES} ${GLFW_DEPENDENCIES})