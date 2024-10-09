add_executable(test_array test_array.cc)
target_include_directories(test_array "${HEADER_DIRS}")
target_link_libraries(test_array MPI::MPI_CXX vt::vt)