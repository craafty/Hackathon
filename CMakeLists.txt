cmake_minimum_required (VERSION 3.16)

project("Hackathon")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glad)
add_subdirectory(libs/glm)
add_subdirectory(libs/assimp)
add_subdirectory(libs/stb_image)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
)
add_executable(${PROJECT_NAME} ${MY_SOURCES})

# debug
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC
ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/"
) 
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC
SOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/"
) 

# release
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC
#ASSETS_PATH="./res/"
#)
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC
#SOURCE_PATH="./src/"
#)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} )

if(MSVC)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
    set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
    set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
endif()

# include directories
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC 
	"${CMAKE_CURRENT_SOURCE_DIR}/include/"
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
	"${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp/build/include"
)

# link libraries
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE 
	glfw 
	glad 
	glm
	stb_image
	${CMAKE_SOURCE_DIR}/libs/assimp/build/lib/Debug/assimp-vc143-mtd.lib
)

# copy assimp dll to build directory after build
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/assimp/build/bin/Debug/assimp-vc143-mtd.dll"
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
)