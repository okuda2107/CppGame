file(GLOB_RECURSE CXX_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp"
)

# 再利用性のため，engine部分だけライブラリ化
add_library(engine_temp ${CXX_FILES})

# エンジンのヘッダファイルを読み込み
# 再帰的にディレクトリのみを取得
file(GLOB INCLUDE_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/*"
)
list(FILTER INCLUDE_ROOT EXCLUDE REGEX "CMakeLists.txt")
target_include_directories(engine_temp PUBLIC ${INCLUDE_ROOT})

target_include_directories(engine_temp PUBLIC ${CMAKE_INCLUDE_PATH})

target_link_directories(engine_temp PUBLIC ${CMAKE_LIBRARY_PATH})

target_link_libraries(engine_temp PRIVATE ${CMAKE_LIBRARIES})
