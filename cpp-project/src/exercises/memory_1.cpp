#include <array>
#include <cstdint>
#include <iostream>
#include <random>
#include <cassert>

#include <CL/sycl.hpp>
namespace sycl = cl::sycl;

int main(int, char**) {
  std::array<int32_t, 16> arr;
  std::mt19937 mt_engine(std::random_device{}());
  std::uniform_int_distribution<int32_t> idist(0, 10);

  std::cout << "Data: ";
  for (auto& el : arr) {
    el = idist(mt_engine);
    std::cout << el << " ";
  }
  std::cout << std::endl;

  sycl::buffer<int32_t, 1> buf(arr.data(), sycl::range<1>(arr.size()));

  // <<Set up queue and check device information>>

  // <<Reduction loop>>

  auto acc = buf.get_access<sycl::access::mode::read>();
  std::cout << "We've set up the SYCL buffer" << std::endl;

  return 0;
}