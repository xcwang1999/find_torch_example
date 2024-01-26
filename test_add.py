import torch

from lib import torch_cmake_example

def test_add():
    a = torch.tensor([1, 2, 3, 4, 5])
    b = torch.tensor([1, 2, 3, 4, 5])

    c = torch_cmake_example.add_tensors(a, b)
    assert torch.all(c == a + b)
    print("test_add passed")
    print(c)

if __name__ ==  "__main__":
    test_add()