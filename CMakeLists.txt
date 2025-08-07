file(GLOB file "src/*.cpp")

cmake_minimum_required(VERSION 3.21)

project(prj CXX)

add_executable(app ${file})

target_include_directories(app PRIVATE "inc")
target_include_directories(app PRIVATE ${CMAKE_INCLUDE_PATH})

target_link_directories(app PRIVATE ${CMAKE_LIBRARY_PATH})

target_link_libraries(app PRIVATE SDL2)
target_link_libraries(app PRIVATE SDL2_image)
target_link_libraries(app PRIVATE SDL2_mixer)
target_link_libraries(app PRIVATE SDL2_net)
target_link_libraries(app PRIVATE SDL2_ttf)
target_link_libraries(app PRIVATE SOIL)
target_link_libraries(app PRIVATE GL GLEW)
