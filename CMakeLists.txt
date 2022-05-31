cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(playing_cards_cpp_threadsafe)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

add_executable(pcts src/aux/probar.cpp src/cards.cpp src/main.cpp)

target_link_libraries(pcts pthread)