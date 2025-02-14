file(GLOB file "src/*.cpp")

cmake_minimum_required(VERSION 3.21)

# 迷い中
# set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
option(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmakes/x64-linux.cmake")

project(prj CXX)

include_directories("/usr/include/SDL2")
include_directories("/usr/include/SOIL")
include_directories("/usr/include/GL")
include_directories("/usr/include/rapidjson")

add_executable(app ${file})

target_include_directories(app PRIVATE "inc")

target_link_libraries(app PRIVATE SDL2)
target_link_libraries(app PRIVATE SDL2_image)
target_link_libraries(app PRIVATE SDL2_mixer)
target_link_libraries(app PRIVATE SDL2_net)
target_link_libraries(app PRIVATE SDL2_ttf)
target_link_libraries(app PRIVATE SOIL)
target_link_libraries(app PRIVATE GL GLEW)
target_link_libraries(app PRIVATE openal alut)
