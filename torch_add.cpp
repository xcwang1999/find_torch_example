#include <torch/extension.h>

torch::Tensor add_tensors(const torch::Tensor& a, 
                          const torch::Tensor& b) {
  return a + b;
}