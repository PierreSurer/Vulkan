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

find_package(Vulkan COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

function(add_shader TARGET SHADER)
    find_program(GLSLC glslc)

    set(current-shader-path ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/${SHADER})
	string(REPLACE "." "_" SHADER ${SHADER})
    set(current-output-path ${CMAKE_BINARY_DIR}/Release/shaders/${SHADER}.spv) #TODO release

    # Add a custom command to compile GLSL to SPIR-V.
    get_filename_component(current-output-dir ${current-output-path} DIRECTORY)
    file(MAKE_DIRECTORY ${current-output-dir})

    add_custom_command(
        OUTPUT ${current-output-path}
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders/"
        COMMAND ${GLSLC} -o ${current-output-path} ${current-shader-path}
        DEPENDS ${current-shader-path}
        IMPLICIT_DEPENDS CXX ${current-shader-path}
        VERBATIM)

    # Make sure our build depends on this output.
    set_source_files_properties(${current-output-path} PROPERTIES GENERATED TRUE)
    target_sources(${TARGET} PRIVATE ${current-output-path})
endfunction(add_shader)

# Find all shaders.
file(GLOB vertex-shaders ${CMAKE_SOURCE_DIR}/src/shaders/*.vert)
file(GLOB fragment-shaders ${CMAKE_SOURCE_DIR}/src/shaders/*.frag)

# Add them to the build.
foreach(vertex-shader ${vertex-shaders})
	get_filename_component(p ${vertex-shader} NAME)
	message("Compiled " ${p})
	add_shader(${PROJECT_NAME} ${p})
endforeach(vertex-shader)

foreach(fragment-shader ${fragment-shaders})
	get_filename_component(p ${fragment-shader} NAME)
	message("Compiled " ${p})
	add_shader(${PROJECT_NAME} ${p})
endforeach(fragment-shader)