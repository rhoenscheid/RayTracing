add_executable(Render main.cpp)
target_link_libraries(Render PUBLIC RayTracer MPI::MPI_CXX OpenMP::OpenMP_CXX)