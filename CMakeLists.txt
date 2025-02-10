set(file Test/TestEigen3.cpp)

cmake_minimum_required(VERSION 3.21)

# 迷い中
option(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmakes/x64-linux.cmake")

project(prj CXX)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_net CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(soil CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

add_executable(app ${file})

target_link_libraries(app
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    )
target_link_libraries(app PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
target_link_libraries(app PRIVATE $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>)
target_link_libraries(app PRIVATE $<IF:$<TARGET_EXISTS:SDL2_net::SDL2_net>,SDL2_net::SDL2_net,SDL2_net::SDL2_net-static>)
target_link_libraries(app PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)
target_link_libraries(app PRIVATE soil)
target_link_libraries(app PRIVATE GLEW::GLEW)
target_link_libraries(app PRIVATE OpenAL::OpenAL)
target_link_libraries(app PRIVATE rapidjson)
