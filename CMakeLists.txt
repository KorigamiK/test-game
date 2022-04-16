cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

set(LOCAL_PROJECT_NAME        "Hello")
set(LOCAL_PROJECT_VERSION     "0.0.1")
set(LOCAL_PROJECT_DESCRIPTION "Description")

# Header files (relative to "include" directory)
set(HEADERS
    header.h
    app.h
    utils.h
)

# Source files (relative to "src" directory)
set(SOURCES
    main.cpp
    utils.cpp
    app.cpp
)

# Compiler definitions
set(DEFINES

)

# Compiler options
set(OPTIONS

)

# Project setup
project(
        ${LOCAL_PROJECT_NAME}
        VERSION ${LOCAL_PROJECT_VERSION}
        DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
        LANGUAGES CXX
    )

add_executable(${LOCAL_PROJECT_NAME})


IF(PLATFORM_PSP)
    
    list(APPEND SOURCES pspInitActions.cpp)
    list(APPEND HEADERS pspInitActions.h)
    list(APPEND DEFINES IS_PSP)

    set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin/psp")
    file(COPY include/assets/funkyFont.ttf DESTINATION ${CMAKE_BINARY_DIR}/bin/psp/assets)

    target_link_libraries(${LOCAL_PROJECT_NAME} PRIVATE
            SDL2main
            SDL2_ttf
            SDL2
            GL
            freetype
            png
            z
            pspvram
            pspdisplay
            pspvfpu
            pspgu
            pspge
            pspdebug
            psphprm
            pspctrl
            pspaudio
        )

        create_pbp_file(
            TARGET ${LOCAL_PROJECT_NAME}
            ICON_PATH NULL
            BACKGROUND_PATH NULL
            PREVIEW_PATH NULL
            TITLE ${LOCAL_PROJECT_NAME}
            BUILD_PRX
        )

ELSE()
    target_link_libraries(${LOCAL_PROJECT_NAME} PRIVATE SDL2main SDL2 SDL2_ttf png freetype)
    set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin/desktop")
    file(COPY include/assets/funkyFont.ttf DESTINATION ${CMAKE_BINARY_DIR}/bin/desktop/assets)

ENDIF()

list(TRANSFORM HEADERS PREPEND "include/")
list(TRANSFORM SOURCES PREPEND "src/")

target_include_directories(${LOCAL_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(${LOCAL_PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
target_compile_definitions(${LOCAL_PROJECT_NAME} PRIVATE ${DEFINES})
target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE ${OPTIONS})
