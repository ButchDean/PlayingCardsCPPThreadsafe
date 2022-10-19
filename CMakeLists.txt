cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(playing_cards_cpp_threadsafe)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(ENABLE_DEVELOPER_MODE TRUE CACHE BOOL "Enable dev mode sanitization")

set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)

include_directories(PlayingCardsCore/includes)

add_subdirectory(PlayingCardsCore)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Building for Mac OS")

    add_library(ProgBarLib STATIC PlayingCardsCore/src/aux/progbar.cc)
    add_library(FunctionalLib STATIC PlayingCardsCore/src/functional.cc)
    add_library(CardsLib STATIC PlayingCardsCore/src/cards.cc)

    add_executable(pcts src/main.cc)

    target_link_libraries(pcts 
                          pthread 
                          ProgBarLib 
                          FunctionalLib
                          CardsLib)    
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Building for Linux")

    add_executable(pcts 
                   src/main.cc
                   PlayingCardsCore/src/aux/progbar.cc
                   PlayingCardsCore/src/functional.cc
                   PlayingCardsCore/src/cards.cc)

    target_link_libraries(pcts 
                          pthread)     
else()
    message(FATAL_ERROR "Only Mac and Linux officially supported.")
endif()

