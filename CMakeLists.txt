cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(playing_cards_cpp_threadsafe)

set(CMAKE_CXX_STANDARD 14)

include_directories(PlayingCardsCore/includes)

add_executable(pcts 
	PlayingCardsCore/src/functional.cc 
	PlayingCardsCore/src/aux/progbar.cc 
	PlayingCardsCore/src/cards.cc src/main.cc)

target_link_libraries(pcts pthread)

# Using GTest for unit testing
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

enable_testing()

add_executable(
    cardstest
    PlayingCardsCore/unittest/cardstest.cc
    PlayingCardsCore/src/aux/progbar.cc
    PlayingCardsCore/src/cards.cc
)

target_link_libraries(
    cardstest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(cardstest)
