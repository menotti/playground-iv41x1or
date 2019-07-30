#include <iostream>

// The SYCL header
#include <SYCL/sycl.hpp>

namespace sycl = cl::sycl;

int main(int argc, char **) {
  // <<Setup host memory>>

  // define input vectors

  // define output vector

  // <<Setup SYCL queue>>
  /** Construct a SYCL queue on the device returned by the
   * device selector of choice */

  // validation checks
  {
    std::cout << "sycl::float4 vectors check - a.w, b.w, c.w:\n"
              << a.w() << ", " << b.w() << ", " << c.w() << std::endl;
    std::cout << "sycl::queue check - selected device:\n"
              << myQueue.get_device().get_info<sycl::info::device::name>()
              << std::endl;
  }

  return 0;
}
