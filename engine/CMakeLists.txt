add_library(engine STATIC)

# find_package()

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


target_link_directories(engine PUBLIC ${CMAKE_LIBRARY_PATH})

target_link_libraries(engine PRIVATE ${CMAKE_LIBRARIES})
