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
if (OPENAL_INCLUDE_DIR AND OPENAL_LIBRARY AND OPENAL_DLL)
    # find_packageでパス解決しようとすると，alut側のinclude pathの解決ができないので，手動で指定
    target_include_directories(engine_temp
        PUBLIC
            ${OPENAL_INCLUDE_DIR}
    )
    target_link_libraries(engine_temp
        PRIVATE
            ${OPENAL_LIBRARY}
    )
    foreach(dll IN LISTS OPENAL_DLL)
        get_filename_component(dll_name "${dll}" NAME_WE)
        add_library(${dll_name} SHARED IMPORTED)
        set_target_properties(${dll_name} PROPERTIES
            IMPORTED_LOCATION "${dll}"
            IMPORTED_IMPLIB ${OPENAL_LIBRARY}
            INTERFACE_INCLUDE_DIRECTORIES ${OPENAL_INCLUDE_DIR}
        )
        target_link_libraries(engine_temp PRIVATE ${dll_name})
    endforeach()
else()
    message(WARNING "not set OPENAL_INCLUDE_PATH, or _LIBRARY, or _DLL")
endif()

# alut
if (ALUT_INCLUDE_DIR AND ALUT_LIBRARY AND ALUT_DLL)
    # find_packageでパス解決しようとすると，alut側のinclude pathの解決ができないので，手動で指定
    target_include_directories(engine_temp
        PUBLIC
            ${ALUT_INCLUDE_DIR}
    )
    target_link_libraries(engine_temp
        PRIVATE
            ${ALUT_LIBRARY}
    )
    foreach(dll IN LISTS ALUT_DLL)
        get_filename_component(dll_name "${dll}" NAME_WE)
        add_library(${dll_name} SHARED IMPORTED)
        set_target_properties(${dll_name} PROPERTIES
            IMPORTED_LOCATION "${dll}"
            IMPORTED_IMPLIB ${ALUT_LIBRARY}
            INTERFACE_INCLUDE_DIRECTORIES ${ALUT_INCLUDE_DIR}
        )
        target_link_libraries(engine_temp PRIVATE ${dll_name})
    endforeach()
else()
    message(WARNING "not set ALUT_INCLUDE_PATH, or _LIBRARY, or _DLL")
endif()

# rapidjson
if (RAPIDJSON_INCLUDE_DIR)
    # rapidjsonはbuildがコケるので，とりあえずヘッダファイルのみ
    target_include_directories(engine_temp
        PUBLIC
            ${RAPIDJSON_INCLUDE_DIR}
    )
else()
    message(WARNING "not set RAPIDJSON_INCLUDE_DIR")
endif()

# SOIL
if (SOIL_INCLUDE_DIR AND SOIL_LIBRARY)
    # find_packageでパス解決しようとすると，alut側のinclude pathの解決ができないので，手動で指定
    target_include_directories(engine_temp
        PUBLIC
            ${SOIL_INCLUDE_DIR}
    )
    target_link_libraries(engine_temp
        PRIVATE
            ${SOIL_LIBRARY}
    )
else()
    message(WARNING "not set SOIL_INCLUDE_PATH, or _LIBRARY")
endif()
