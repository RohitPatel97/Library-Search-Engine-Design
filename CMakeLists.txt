cmake_minimum_required(VERSION 3.20)

project(LibrarySearchEngineDesign LANGUAGES CXX)

add_executable(library_search_engine
  src/main.cpp
  src/Book.cpp
)

target_include_directories(library_search_engine PRIVATE include)
target_compile_features(library_search_engine PRIVATE cxx_std_20)
set_target_properties(library_search_engine PROPERTIES CXX_EXTENSIONS OFF)

if(MSVC)
  target_compile_options(library_search_engine PRIVATE /W4)
else()
  target_compile_options(library_search_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()
