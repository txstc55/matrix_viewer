cmake_minimum_required(VERSION 2.8.12)
project(matrix_viewer)



set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/)



### Add src to the include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
### Compile all the cpp files in src
file(GLOB SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)


### add tbb
add_subdirectory(${THIRD_PARTY_DIR}tbb)
set(TBB_BUILD_STATIC ON CACHE BOOL " " FORCE)
set(TBB_BUILD_SHARED OFF CACHE BOOL " " FORCE)
set(TBB_BUILD_TBBMALLOC OFF CACHE BOOL " " FORCE)
set(TBB_BUILD_TBBMALLOC_PROXY OFF CACHE BOOL " " FORCE)
set(TBB_BUILD_TESTS OFF CACHE BOOL " " FORCE)


### add eigen
add_subdirectory(${THIRD_PARTY_DIR}eigen-git-mirror)


add_compile_options(-std=c++11 -march=native)


add_executable(${PROJECT_NAME}_bin ${SOURCES})


target_link_libraries(${PROJECT_NAME}_bin ncurses tbb_static eigen)
