cmake_minimum_required(VERSION 3.25)
project(find_torch_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import torch; print(torch.__file__)"
    OUTPUT_VARIABLE TORCH_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REGEX REPLACE "__init__.py$" "" TORCH_PATH "${TORCH_PATH}")
set(Torch_DIR "${TORCH_PATH}/share/cmake/Torch")
find_package(Torch REQUIRED)

add_executable(find_torch_example main.cpp)

target_include_directories(find_torch_example PRIVATE "${TORCH_INCLUDE_DIRS}")

target_link_libraries(find_torch_example PRIVATE "${TORCH_LIBRARIES}")

