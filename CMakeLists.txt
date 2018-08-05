cmake_minimum_required(VERSION 2.6)
project(simple-game-engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

IF (WIN32)
    set(SDL2_PATH "${PROJECT_SOURCE_DIR}/dependencies/SDL2-2.0.5")
    set(SDL2_TTF_PATH "${PROJECT_SOURCE_DIR}/dependencies/SDL2_ttf-2.0.14")
    set(SDL2_IMAGE_PATH "${PROJECT_SOURCE_DIR}/dependencies/SDL2_image-2.0.1")

    ## To test if the host (not the build) is x64:
    ## "$ENV{PROCESSOR_ARCHITEW6432}" STREQUAL "AMD64"
    IF(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
        SET(WIN64 ON)
        SET(DEPENDENCY_FOLDER "${DEPENDENCY_FOLDER}64")
    ELSE(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
        SET(WIN64 OFF)
        SET(DEPENDENCY_FOLDER "${DEPENDENCY_FOLDER}32")
    ENDIF(${CMAKE_SIZEOF_VOID_P} EQUAL 8)

ENDIF(WIN32)

find_package(SDL2_ttf REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    )


# Build Game.
file(GLOB src_files src/*.cpp src/*/*.cpp)
add_library(game_engine_lib ${src_files})
target_link_libraries(game_engine_lib ${SDL2_LIBRARY})
target_link_libraries(game_engine_lib ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(game_engine_lib ${SDL2_TTF_LIBRARIES})


# Build instructions for Platformer Game.
file(GLOB platformer_game_files
    main.cpp)
add_executable(game ${platformer_game_files})
target_link_libraries(game game_engine_lib)

 add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${PROJECT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:game>/assets")

IF (WIN32)

    IF (WIN64)
        set(DLL_DIR "${PROJECT_SOURCE_DIR}/dependencies/dll64")
    ELSE (WIN64)
        set(DLL_DIR "${PROJECT_SOURCE_DIR}/dependencies/dll32")
    ENDIF (WIN64)

    add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${DLL_DIR}"
        "$<TARGET_FILE_DIR:game>")

endif(WIN32)
