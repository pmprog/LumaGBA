
# Correct game name here
project(luma C CXX)

#cmake_minimum_required(VERSION 2.8)

INCLUDE(CheckCXXCompilerFlag)
INCLUDE(CheckCCompilerFlag)

add_definitions(-DLIBALLEGRO5)

# Locate Allegro
FIND_PATH(ALLEGRO_INCLUDE_DIR allegro5/allegro.h)
FIND_LIBRARY(ALLEGRO_LIB liballegro.so allegro.lib)
FIND_LIBRARY(ALLEGRO_COLOUR_LIB liballegro_color.so allegro_color.lib)
FIND_LIBRARY(ALLEGRO_PRIMITIVES_LIB liballegro_primitives.so allegro_primitives.lib)
FIND_LIBRARY(ALLEGRO_AUDIO_LIB liballegro_audio.so allegro_audio.lib)
FIND_LIBRARY(ALLEGRO_ACODEC_LIB liballegro_acodec.so allegro_acodec.lib)
FIND_LIBRARY(ALLEGRO_IMAGE_LIB liballegro_image.so allegro_image.lib)
FIND_LIBRARY(ALLEGRO_FONT_LIB liballegro_font.so allegro_font.lib)
FIND_LIBRARY(ALLEGRO_TTF_LIB liballegro_ttf.so allegro_ttf.lib)

# Locate ENet
FIND_LIBRARY(ENET_LIB libenet.so libenet.a enet.lib)

# Build resources
IF(CMAKE_HOST_WIN32)
        execute_process(COMMAND ./0construct.cmd WORKING DIRECTORY ./resources)
ENDIF()
IF(CMAKE_HOST_UNIX)
        execute_process(COMMAND ./0construct.sh WORKING DIRECTORY ./resources)
ENDIF()

# Add game source code folders here
aux_source_directory(./source SRC_LIST)
aux_source_directory(./engine SRC_LIST)
aux_source_directory(./engine/a5 SRC_LIST)
aux_source_directory(./resources SRC_LIST)

# Build the executable
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Link all the libaries
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
        ${ENET_LIB}
        ${ALLEGRO_LIB}
        ${ALLEGRO_COLOUR_LIB}
        ${ALLEGRO_PRIMITIVES_LIB}
        ${ALLEGRO_AUDIO_LIB}
        ${ALLEGRO_ACODEC_LIB}
        ${ALLEGRO_IMAGE_LIB}
        ${ALLEGRO_FONT_LIB}
        ${ALLEGRO_TTF_LIB}
        )

