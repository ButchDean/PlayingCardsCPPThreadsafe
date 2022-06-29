cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(playing_cards_cpp_threadsafe)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ENABLE_DEVELOPER_MODE TRUE CACHE BOOL "Enable dev mode sanitization")

set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)

include_directories(includes)

add_library(ProgBarLib STATIC src/aux/progbar.cc)
add_library(FunctionalLib STATIC src/functional.cc)
add_library(CardsLib STATIC src/cards.cc)

add_executable(pcts src/main.cc)

target_link_libraries(pcts 
                      pthread 
                      ProgBarLib 
                      FunctionalLib
                      CardsLib)

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
    unittest/cardstest.cc
)

target_link_libraries(
    cardstest
    ProgBarLib
    FunctionalLib
    CardsLib
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(cardstest)