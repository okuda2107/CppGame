add_library(engine STATIC)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE CXX_FILES CONFIGURE_DEPENDS
    "src/**/*.cpp"
)

file(GLOB_RECURSE PRIVATE_HEADERS CONFIGURE_DEPENDS
    "src/**/*.h"
)

file(GLOB_RECURSE PUBLIC_HEAKERS CONFIGURE_DEPENDS
    "include/**/*.h"
)

target_sources(engine
    PRIVATE
        ${CXX_FILES}

    PRIVATE
        FILE_SET privateHeaders
        TYPE HEADERS
        BASE_DIRS
            "src"
        FILES
            ${PRIVATE_HEADERS}

    PUBLIC
        FILE_SET publicHeaders
        TYPE HEADERS
        BASE_DIRS
            "include"
        FILES
            ${PUBLIC_HEADERS}
)

target_link_libraries(engine
    PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        SDL2_mixer::SDL2_mixer
        SDL2_net::SDL2_net
        SDL2_ttf::SDL2_ttf
        GLEW::glew_s
)

if (OPENAL_INCLUDE_PATH)
    target_include_directories(engine_temp
        PUBLIC
            ${OPENAL_INCLUDE_PATH}
    )
else()
    message(WARNING "not set OPENAL_INCLUDE_PATH")
endif()

if (OPENAL_LIBRARY_PATH)
    target_link_directories(engine_temp
        PRIVATE
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

if (ALUT_INCLUDE_PATH)
    target_include_directories(engine
        PUBLIC
            ${ALUT_INCLUDE_PATH}
    )
endif()

if (ALUT_LIBRARY)
    target_link_libraries(engine
        PRIVATE
            ${ALUT_LIBRARY}
    )
endif()

if (RAPIDJSON_INCLUDE_PATH)
    # rapidjsonはbuildがコケるので，とりあえずヘッダファイルのみ
    target_include_directories(engine
        PUBLIC
            ${RAPIDJSON_INCLUDE_PATH}
    )
endif()
