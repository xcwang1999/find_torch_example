#include <torch/torch.h>
#include <pybind11/pybind11.h>

int main(){
  torch::Tensor tensor = torch::rand({2, 3});
  std::cout << tensor << std::endl;
  return 0;
}