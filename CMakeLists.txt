file(GLOB CXX_FILES
    "engine/*/*.cpp"
)

cmake_minimum_required(VERSION 3.21)

project(prj CXX)

add_executable(app ${CXX_FILES})

# エンジンのヘッダファイルを読み込み
# 再帰的にディレクトリのみを取得
file(GLOB_RECURSE INCLUDE_DIR LIST_DIRECTORIES true
    "${CMAKE_SOURCE_DIR}engine/*"
)
target_include_directories(app PRIVATE ${INCLUDE_DIR})

target_include_directories(app PRIVATE ${CMAKE_INCLUDE_PATH})

target_link_directories(app PRIVATE ${CMAKE_LIBRARY_PATH})

target_link_libraries(app PRIVATE ${SDL2_LIBRARY})
target_link_libraries(app PRIVATE SDL2_image)
target_link_libraries(app PRIVATE SDL2_mixer)
target_link_libraries(app PRIVATE SDL2_net)
target_link_libraries(app PRIVATE SDL2_ttf)
target_link_libraries(app PRIVATE SOIL)
target_link_libraries(app PRIVATE ${OPENGL_LIBRARY})

set(RELEASE_DIR "${CMAKE_SOURCE_DIR}/Release")
add_custom_command(
    TARGET app
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:app> ${RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_DLL} ${RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GLEW_DLL} ${RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Assets" "${RELEASE_DIR}/Assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Shaders" "${RELEASE_DIR}/Shaders"
)
