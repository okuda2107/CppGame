file(GLOB_RECURSE CXX_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp"
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)

# 再利用性のため，engine部分だけライブラリ化
add_library(engine_temp ${CXX_FILES})

# エンジンのヘッダファイルを読み込み
# 再帰的にディレクトリのみを取得
file(GLOB INCLUDE_ROOT
    "${CMAKE_CURRENT_SOURCE_DIR}/*"
)
list(FILTER INCLUDE_ROOT EXCLUDE REGEX "CMakeLists.txt")
target_include_directories(engine_temp PUBLIC ${INCLUDE_ROOT})

target_link_libraries(engine_temp
    PRIVATE
        SDL2::SDL2main
        SDL2_mixer::SDL2_mixer
        SDL2_net::SDL2_net
        SDL2_ttf::SDL2_ttf
        GLEW::glew_s
    PUBLIC
        SDL2::SDL2
        SDL2_image::SDL2_image
)

# OpenAL
if (OPENAL_INCLUDE_PATH)
    # find_packageでパス解決しようとすると，alut側のinclude pathの解決ができないので，手動で指定
    target_include_directories(engine_temp
        PUBLIC
            ${OPENAL_INCLUDE_PATH}
    )
else()
    message(WARNING "not set OPENAL_INCLUDE_PATH")
endif()

if (OPENAL_LIBRARY_PATH)
    target_link_directories(engine_temp
        PUBLIC
            ${OPENAL_LIBRARY_PATH}
    )
else()
    message(WARNING "not set OPENAL_LIBRARY_PATH")
endif()

if (OPENAL_LIBRARY)
    target_link_libraries(engine_temp
        PRIVATE
            ${OPENAL_LIBRARY}
    )
else()
    message(WARNING "not set OPENAL_LIBRARY")
endif()

# alut
if (ALUT_INCLUDE_PATH)
    target_include_directories(engine_temp
        PUBLIC
            ${ALUT_INCLUDE_PATH}
    )
else()
    message(WARNING "not set ALUT_INCLUDE_PATH")
endif()

if (ALUT_LIBRARY_PATH)
    target_link_directories(engine_temp
        PUBLIC
            ${ALUT_LIBRARY_PATH}
    )
else()
    message(WARNING "not set ALUT_LIBRARY_PATH")
endif()

if (ALUT_LIBRARY)
    target_link_libraries(engine_temp
        PRIVATE
            ${ALUT_LIBRARY}
    )
else()
    message(WARNING "not set ALUT_LIBRARY")
endif()

# rapidjson
if (RAPIDJSON_INCLUDE_PATH)
    # rapidjsonはbuildがコケるので，とりあえずヘッダファイルのみ
    target_include_directories(engine_temp
        PUBLIC
            ${RAPIDJSON_INCLUDE_PATH}
    )
else()
    message(WARNING "not set RAPIDJSON_INCLUDE_PATH")
endif()

# SOIL
if (SOIL_INCLUDE_PATH)
    target_include_directories(engine_temp
        PUBLIC
            ${SOIL_INCLUDE_PATH}
    )
else()
    message(WARNING "not set SOIL_INCLUDE_PATH")
endif()

if (SOIL_LIBRARY_PATH)
    target_link_directories(engine_temp
        PUBLIC
            ${SOIL_LIBRARY_PATH}
    )
else()
    message(WARNING "not set SOIL_LIBRARY_PATH")
endif()

if (SOIL_LIBRARY)
    target_link_libraries(engine_temp
        PRIVATE
            ${SOIL_LIBRARY}
    )
else()
    message(WARNING "not set SOIL_LIBRARY")
endif()
