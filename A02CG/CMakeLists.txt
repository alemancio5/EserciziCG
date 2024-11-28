#########################################################
#                       Variables                       #
# Set them to match your SDK and libraries installation #
#https://stackoverflow.com/questions/47718196/glfw3-library-in-clion-with-cmake-causes-undefined-symbols-on-macos
#########################################################

set($ENV{VULKAN_SDK} "/Library/Added/Vulkan/1.3.275.0/macOS")      # Vulkan SDK
set(GLFW "/Library/Added/Vulkan/libs/glfw-3.4.bin.MACOS")  # GLFW
set(GLM "/Library/Added/Vulkan/libs/glm")                    # GLM
# List of directories to add to the include path:
# all headers in these directories can be included in the source code
# (Vulkan headers must be omitted from here)
list(APPEND INCLUDE_DIRS "${GLFW}/include" ${GLM} headers)

# List of libraries to link to the executable:
# all these libraries will be linked to the compiled executable
# (Vulkan library must be omitted from here)
list(APPEND LINK_LIBS "${GLFW}/lib-arm64/libglfw3.a")
#list(APPEND LINK_LIBS "${GLFW}/lib-arm64/libglfw.3.dylib")
# Name of the project, will be used as the target name for CMake build
# and will be the name of the executable
set(PROJ_NAME A02CG)
# Name of the source file containing the main() function
set(MAIN A02.cpp)


cmake_minimum_required(VERSION 3.24)
project(A02CG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")

add_executable(A02CG A02.cpp)


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