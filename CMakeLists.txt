cmake_minimum_required(VERSION 3.14)

project(AVT VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(prohibit_in_source_build)

include(setup_vt)

include_directories( "${CMAKE_CURRENT_BINARY_DIR}")
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/include/")

add_executable(avt src/avt.cc)
target_include_directories(avt "${HEADER_DIRS}")
target_link_libraries(avt MPI::MPI_CXX vt::vt)

option( AVT_ENABLE_TESTS "Build tests" ON)
if ( AVT_ENABLE_TESTS )
add_subdirectory(tests)
endif()

