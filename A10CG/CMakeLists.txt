set($ENV{VULKAN_SDK} "/Library/Added/Vulkan/1.3.275.0/macOS")      # Vulkan SDK
set(GLFW "/Library/Added/Vulkan/libs/glfw-3.4.bin.MACOS")  # GLFW
set(GLM "/Library/Added/Vulkan/libs/glm")                    # GLM
list(APPEND INCLUDE_DIRS "${GLFW}/include" ${GLM} headers)
list(APPEND LINK_LIBS "${GLFW}/lib-arm64/libglfw3.a")
set(PROJ_NAME A10CG)
set(MAIN A10.cpp)

cmake_minimum_required(VERSION 3.24)
project(A10CG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")

add_executable(A10CG A10.cpp)

find_package(Vulkan REQUIRED)

foreach(dir IN LISTS Vulkan_INCLUDE_DIR INCLUDE_DIRS)
    target_include_directories(${PROJECT_NAME} PUBLIC ${dir})
endforeach()
foreach(lib IN LISTS Vulkan_LIBRARIES LINK_LIBS)
    target_link_libraries(${PROJECT_NAME} ${lib})
endforeach()

file(COPY ${CMAKE_CURRENT_LIST_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_LIST_DIR}/modules DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_LIST_DIR}/textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})