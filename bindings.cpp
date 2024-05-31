#include <pybind11/pybind11.h>

void build_module(pybind11::module &m); 

PYBIND11_MODULE(torch_cmake_example, m) {
  build_module(m);
}
