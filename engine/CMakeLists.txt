file(GLOB_RECURSE CXX_FILES CONFIGURE_DEPENDS
    "src/**/*.cpp"
)

# 再利用性のため，engine部分だけライブラリ化
add_library(engine ${CXX_FILES})

# エンジンのヘッダファイルを読み込み
target_include_directories(engine
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(engine PUBLIC ${CMAKE_INCLUDE_PATH})

target_link_directories(engine PUBLIC ${CMAKE_LIBRARY_PATH})

target_link_libraries(engine PRIVATE ${CMAKE_LIBRARIES})
