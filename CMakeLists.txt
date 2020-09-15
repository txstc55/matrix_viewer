cmake_minimum_required(VERSION 2.8.12)
project(matrix_viewer)



set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/)



### Add src to the include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
### Compile all the cpp files in src
file(GLOB SOURCES
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

### add eigen
add_subdirectory(${THIRD_PARTY_DIR}eigen)

### add tbb
set(TBB_BUILD_STATIC ON CACHE BOOL " " FORCE)
set(TBB_BUILD_SHARED OFF CACHE BOOL " " FORCE)
set(TBB_BUILD_TBBMALLOC OFF CACHE BOOL " " FORCE)
set(TBB_BUILD_TBBMALLOC_PROXY OFF CACHE BOOL " " FORCE)
set(TBB_BUILD_TESTS OFF CACHE BOOL " " FORCE)
add_subdirectory(${THIRD_PARTY_DIR}tbb)

set_property(TARGET tbb_static tbb_def_files PROPERTY FOLDER "dependencies")
target_compile_definitions(tbb_static PUBLIC -DUSE_TBB)

# add_subdirectory(${THIRD_PARTY_DIR}opencv)

FIND_PACKAGE( OpenCV REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
message(STATUS "Opencv lib location ${OpenCV_LIBS}")
### settings
set(BUILD_TESTING OFF CACHE BOOL " " FORCE)

add_compile_options(-std=c++11 -march=native)
add_executable(${PROJECT_NAME}_bin ${SOURCES})
target_link_libraries(${PROJECT_NAME}_bin ${OpenCV_LIBS} ncurses tbb_static eigen)
