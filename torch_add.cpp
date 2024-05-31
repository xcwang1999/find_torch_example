#include <torch/extension.h>

torch::Tensor add_tensors(const torch::Tensor& a, 
                          const torch::Tensor& b) {
  return a + b;
}

void build_module(pybind11::module &m) {
  m.def("add_tensors", &add_tensors, "Add two tensors");
}
