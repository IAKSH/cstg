cmake_minimum_required(VERSION 3.0.0)
project(cstg VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(gameplay)
target_sources(gameplay PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/gameplay.c
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/gameplay.h
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/message.c
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/message.h
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/hook.c
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/hook.h
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/gameobject.c
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/gameobject.h
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/gomanager.c
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/gomanager.h
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/drawsort.c
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/drawsort.h
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/audiomanager.c
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/audiomanager.h
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/textdisplay.c
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/textdisplay.h
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/animation.c
    ${CMAKE_CURRENT_LIST_DIR}/gameplay/animation.h
    ) 

target_include_directories(gameplay PUBLIC ${CMAKE_CURRENT_LIST_DIR}/utools)

add_library(customsrc)

target_sources(customsrc PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/customsrc/custom_go_player.c
    ${CMAKE_CURRENT_LIST_DIR}/customsrc/custom_go_player.h
    ${CMAKE_CURRENT_LIST_DIR}/customsrc/custom_go_monster.c
    ${CMAKE_CURRENT_LIST_DIR}/customsrc/custom_go_monster.h
    ${CMAKE_CURRENT_LIST_DIR}/customsrc/custom_gameobjects.c
    ${CMAKE_CURRENT_LIST_DIR}/customsrc/custom_gameobjects.h
    )

target_include_directories(customsrc PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/gameplay
    ${CMAKE_CURRENT_LIST_DIR}/utools
    )

add_library(utools)
target_sources(utools PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/utools/utools.c
    ${CMAKE_CURRENT_LIST_DIR}/utools/utools.h
    ${CMAKE_CURRENT_LIST_DIR}/utools/linklist.c
    ${CMAKE_CURRENT_LIST_DIR}/utools/linklist.h
    ${CMAKE_CURRENT_LIST_DIR}/utools/function.h
    ${CMAKE_CURRENT_LIST_DIR}/utools/hashtable.c
    ${CMAKE_CURRENT_LIST_DIR}/utools/hashtable.h
    ${CMAKE_CURRENT_LIST_DIR}/utools/hashfunc.c
    ${CMAKE_CURRENT_LIST_DIR}/utools/hashfunc.h
    )

add_executable(cstg ${CMAKE_CURRENT_LIST_DIR}/engine/main.c)
target_include_directories(cstg PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/gameplay
    ${CMAKE_CURRENT_LIST_DIR}/customsrc
    ${CMAKE_CURRENT_LIST_DIR}/utools
    )

target_link_libraries(cstg PUBLIC gameplay customsrc utools SDL2 SDL2_image SDL2_mixer SDL2_ttf)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
