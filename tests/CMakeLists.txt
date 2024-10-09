add_executable(test_array test_array.cc)
target_include_directories(test_array PRIVATE "${HEADER_DIR}")
target_link_libraries(test_array PRIVATE MPI::MPI_CXX vt::lib::detector vt::lib::checkpoint vt::runtime::vt)