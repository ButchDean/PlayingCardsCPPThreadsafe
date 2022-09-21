cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(playing_cards_cpp_threadsafe)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(ENABLE_DEVELOPER_MODE TRUE CACHE BOOL "Enable dev mode sanitization")

set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)

include_directories(PlayingCardsCore/includes)

add_subdirectory(PlayingCardsCore)

add_executable(pcts src/main.cc)

target_link_libraries(pcts 
                      pthread 
                      ProgBarLib 
                      FunctionalLib
                      CardsLib)