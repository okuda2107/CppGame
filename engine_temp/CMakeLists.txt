file(GLOB_RECURSE CXX_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp"
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenAL REQUIRED)

# 再利用性のため，engine部分だけライブラリ化
add_library(engine_temp ${CXX_FILES})


# エンジンのヘッダファイルを読み込み
# 再帰的にディレクトリのみを取得
file(GLOB INCLUDE_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/*"
)
list(FILTER INCLUDE_ROOT EXCLUDE REGEX "CMakeLists.txt")
target_include_directories(engine_temp PUBLIC ${INCLUDE_ROOT})

target_link_directories(engine_temp PUBLIC ${CMAKE_LIBRARY_PATH})

target_link_libraries(engine_temp PRIVATE ${CMAKE_LIBRARIES})

target_link_libraries(engine_temp
    PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_mixer::SDL2_mixer
        SDL2_net::SDL2_net
        SDL2_ttf::SDL2_ttf
        GLEW::GLEW
        ${OPENAL_LIBRARY}
)

if (ALUT_INCLUDE_PATH)
    target_include_directories(engine_temp
        PUBLIC
            ${ALUT_INCLUDE_PATH}
    )
endif()

if (ALUT_LIBRARY)
    target_link_libraries(engine_temp
        PRIVATE
            ${ALUT_LIBRARY}
    )
endif()

if (RAPIDJSON_INCLUDE_PATH)
    # rapidjsonはbuildがコケるので，とりあえずヘッダファイルのみ
    target_include_directories(engine_temp
        PUBLIC
            ${RAPIDJSON_INCLUDE_PATH}
    )
endif()
