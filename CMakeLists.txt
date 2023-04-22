cmake_minimum_required(VERSION 3.0)
project(libtorch)

set(CMAKE_PREFIX_PATH  "/home/solidworks/my_install/libtorch")
# find_package(Torch REQUIRED)
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
add_executable(libtorch libtorch.cpp)
target_link_libraries(libtorch "${TORCH_LIBRARIES}")
