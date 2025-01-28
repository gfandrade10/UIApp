cmake_minimum_required(VERSION 3.16)
project(FirstUIProject)
set(MAINDIR ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MAINDIR})
set(LOCAL_INC ${MAINDIR}/includes)
set(IMGUI "F:/C_C++ coding/cppLibs/imgui")
set(GLFW "F:/C_C++ coding/cppLibs/glfw")

set(CMAKE_CXX_FLAGS "-g")

add_subdirectory(src)

find_package(Threads REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${IMGUI}
    ${IMGUI}/backends
    ${GLFW}/include
    ${LOCAL_INC}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GLFW}/lib-mingw-w64/libglfw3dll.a
    ${GLFW}/lib-mingw-w64/libglfw3.a
    opengl32
    Threads::Threads
)

target_compile_options(${PROJECT_NAME} PUBLIC -O2 -Wall -Werror -Wpedantic)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "UIApp") 
