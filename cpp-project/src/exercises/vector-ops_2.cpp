#include <iostream>

// The SYCL header
#include <SYCL/sycl.hpp>

namespace sycl = cl::sycl;

/* This forward declaration will be explained in the next section */
class vector_addition;

int main(int argc, char **) {
  // <<Setup host memory>>
  // define input vectors
  sycl::float4 a = {1.0, 1.0, 1.0, 1.0}; // input 1
  sycl::float4 b = {1.0, 1.0, 1.0, 1.0}; // input 2
  // define output vector
  sycl::float4 c = {0.0, 0.0, 0.0, 0.0}; // output

  // <<Setup SYCL queue>>
  sycl::queue myQueue(sycl::default_selector{});

  // Begin SYCL scope
  {
    // <<Setup device memory>>

    // define input buffers

    // define output buffer

    // Submit a command group functor for execution on a queue. This functor
    // encapsulates the kernel and the data needed for its execution.
    myQueue.submit([&](sycl::handler &cgh) {
      // <<Request device memory access>>

      // read accessors

      // write accessor

      cgh.single_task<class vector_addition>([=]() { /* ... */ });
    });

    // validation checks
    {
      // check buffer via create host accessor
      auto host_c = buf_c.get_access<sycl::access::mode::read>();
      std::cout << "We have successfully set up and accessed device memory!\n";
    }
  }
  // End SYCL scope

  return 0;
}
