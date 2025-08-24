# toolchainで指定しなければならない変数
# - CMAKE_INCLUDE_PATH: 外部ライブラリのinclude path
# - CMAKE_LIBRARY_PATH: 外部ライブラリのlib path
# - CMAKE_LIBRARIES: 外部ライブラリのlibファイル名
# - DLL_FILES: 外部ライブラリの動的ライブラリのpath

cmake_minimum_required(VERSION 3.21)

project(prj CXX)

add_subdirectory("engine")

add_subdirectory("test")

set(RELEASE_DIR "${CMAKE_SOURCE_DIR}/Release")
add_custom_target(Release ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:app> ${RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DLL_FILES} ${RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ROOT_DIR}/Assets" "${RELEASE_DIR}/Assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${ROOT_DIR}/Shaders" "${RELEASE_DIR}/Shaders"
    DEPENDS app
)
