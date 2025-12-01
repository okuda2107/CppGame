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
    target_include_directories(engine
        PUBLIC
            ${OPENAL_INCLUDE_PATH}
    )
else()
    message(WARNING "not set OPENAL_INCLUDE_PATH")
endif()

if (OPENAL_LIBRARY_PATH)
    target_link_directories(engine
        PUBLIC
            ${OPENAL_LIBRARY_PATH}
    )
else()
    message(WARNING "not set OPENAL_LIBRARY_PATH")
endif()

if (OPENAL_LIBRARY)
    target_link_libraries(engine
        PRIVATE
            ${OPENAL_LIBRARY}
    )
else()
    message(WARNING "not set OPENAL_LIBRARY")
endif()


# alut
if (ALUT_INCLUDE_PATH)
    target_include_directories(engine
        PUBLIC
            ${ALUT_INCLUDE_PATH}
    )
else()
    message(WARNING "not set ALUT_INCLUDE_PATH")
endif()

if (ALUT_LIBRARY_PATH)
    target_link_directories(engine
        PUBLIC
            ${ALUT_LIBRARY_PATH}
    )
else()
    message(WARNING "not set ALUT_LIBRARY_PATH")
endif()

if (ALUT_LIBRARY)
    target_link_libraries(engine
        PRIVATE
            ${ALUT_LIBRARY}
    )
else()
    message(WARNING "not set ALUT_LIBRARY")
endif()


# rapidjson
if (RAPIDJSON_INCLUDE_PATH)
    # rapidjsonはbuildがコケるので，とりあえずヘッダファイルのみ
    target_include_directories(engine
        PUBLIC
            ${RAPIDJSON_INCLUDE_PATH}
    )
else()
    message(WARNING "not set RAPIDJSON_INCLUDE_PATH")
endif()


# SOIL
if (SOIL_INCLUDE_PATH)
    target_include_directories(engine
        PUBLIC
            ${SOIL_INCLUDE_PATH}
    )
else()
    message(WARNING "not set SOIL_INCLUDE_PATH")
endif()

if (SOIL_LIBRARY_PATH)
    target_link_directories(engine
        PUBLIC
            ${SOIL_LIBRARY_PATH}
    )
else()
    message(WARNING "not set SOIL_LIBRARY_PATH")
endif()

if (SOIL_LIBRARY)
    target_link_libraries(engine
        PRIVATE
            ${SOIL_LIBRARY}
    )
else()
    message(WARNING "not set SOIL_LIBRARY")
endif()
