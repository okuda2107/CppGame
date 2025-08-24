file(GLOB_RECURSE CXX_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/../engine/*/*.cpp"
)

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/*/*.cpp"
)

cmake_minimum_required(VERSION 3.14)

project(prj)

# エンジンの実装を取り込むためにライブラリ化して組み込む
add_library(engineLib ${CXX_FILES})
# エンジンのヘッダファイルを読み込み
# 再帰的にディレクトリのみを取得
file(GLOB INCLUDE_ROOT
    "${CMAKE_SOURCE_DIR}/../engine/*"
)
target_include_directories(engineLib PUBLIC ${INCLUDE_ROOT})

target_include_directories(engineLib PUBLIC ${CMAKE_INCLUDE_PATH})

target_link_directories(engineLib PUBLIC ${CMAKE_LIBRARY_PATH})

target_link_libraries(engineLib PRIVATE ${SDL2_LIBRARY})
target_link_libraries(engineLib PRIVATE SDL2_image)
target_link_libraries(engineLib PRIVATE SDL2_mixer)
target_link_libraries(engineLib PRIVATE SDL2_net)
target_link_libraries(engineLib PRIVATE SDL2_ttf)
target_link_libraries(engineLib PRIVATE SOIL)
target_link_libraries(engineLib PRIVATE ${OPENAL_LIBRARY})
target_link_libraries(engineLib PRIVATE ${OPENGL_LIBRARY})

add_subdirectory("${CMAKE_SOURCE_DIR}/../exlibs/googletest-1.17.0" "${CMAKE_SOURCE_DIR}/../exlibs/googletest-1.17.0/build")

enable_testing()

# add_executable(testApp "${TEST_FILES}")
add_executable(testApp test.cpp)

target_link_libraries(testApp PRIVATE GTest::gtest_main engineLib)

include(GoogleTest)

gtest_discover_tests(testApp)
