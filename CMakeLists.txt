cmake_minimum_required(VERSION 2.8.12)
project(matrix_viewer)



set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/)



### Add src to the include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
### Compile all the cpp files in src
file(GLOB SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)




add_compile_options(-std=c++11 -O3)


add_executable(${PROJECT_NAME}_bin ${SOURCES})



add_compile_options(-print-file-name=library)
set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
if (WIN32)
  set(tbb_debug_postfix "_debug") # to fit pragmas in _windef.h inside TBB
endif()

target_link_libraries(${PROJECT_NAME}_bin ncurses)
