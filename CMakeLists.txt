cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

# set the project name
set(PROJECT_NAME "Vulkan")
project(${PROJECT_NAME} VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
  SYSTEM "${PROJECT_SOURCE_DIR}/Libraries"
  SYSTEM "${PROJECT_SOURCE_DIR}/Libraries/glm"
)

add_subdirectory("${PROJECT_SOURCE_DIR}/Libraries/glfw-3.3.6")

target_link_libraries(${PROJECT_NAME} glfw)


find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIR})