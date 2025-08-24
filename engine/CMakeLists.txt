file(GLOB_RECURSE CXX_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp"
)

file(GLOB ENTRY_POINT
    "${CMAKE_CURRENT_SOURCE_DIR}/core/Main.cpp"
)

list(FILTER CXX_FILES EXCLUDE REGEX "${ENTRY_POINT}")

# 再利用性のため，engine部分だけライブラリ化
add_library(engine ${CXX_FILES})

# エンジンのヘッダファイルを読み込み
# 再帰的にディレクトリのみを取得
file(GLOB INCLUDE_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/*"
)
list(FILTER INCLUDE_ROOT EXCLUDE REGEX "CMakeLists.txt")
target_include_directories(engine PUBLIC ${INCLUDE_ROOT})

target_include_directories(engine PUBLIC ${CMAKE_INCLUDE_PATH})

target_link_directories(engine PRIVATE ${CMAKE_LIBRARY_PATH})

target_link_libraries(engine PRIVATE ${CMAKE_LIBRARIES})

add_executable(app ${ENTRY_POINT})

target_link_libraries(app PRIVATE engine)
