#include <pybind11/pybind11.h>
#include <torch/extension.h>

torch::Tensor add_tensors(const torch::Tensor& a, 
                          const torch::Tensor& b);

namespace py = pybind11;

PYBIND11_MODULE(torch_cmake_example, m) {
  m.def("add_tensors", &add_tensors, "Add two tensors");
}

