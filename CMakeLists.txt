cmake_minimum_required(VERSION 3.25)
project(torch_cmake_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

execute_process(
    COMMAND "${Python3_EXECUTABLE}" -c "import sysconfig; print(sysconfig.get_path('include'))"
    OUTPUT_VARIABLE PYTHON_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(PYTHON_INCLUDE_DIR EQUAL "")
    message(FATAL_ERROR "Can not find Python include directory.")
else()
    message(STATUS "Python include dir: ${PYTHON_INCLUDE_DIR}")
endif()

execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import torch; print(torch.__file__)"
    OUTPUT_VARIABLE TORCH_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REGEX REPLACE "__init__.py$" "" TORCH_PATH "${TORCH_PATH}")
set(Torch_DIR "${TORCH_PATH}/share/cmake/Torch")
find_package(Torch REQUIRED)

find_package(Git REQUIRED)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    message(STATUS "Populating Git submodule.")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR 
                "git submodule updata --init --recursive failed with ${GIT_SUBMOD_RESULT}.")
    endif()
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(third-party/pybind11)

add_executable(torch_cmake_example main.cpp)

target_include_directories(torch_cmake_example PUBLIC 
        ${PYTHON_INCLUDE_DIR}
        )

target_link_libraries(torch_cmake_example PUBLIC 
        ${TORCH_LIBRARIES}
        pybind11::pybind11
        )
