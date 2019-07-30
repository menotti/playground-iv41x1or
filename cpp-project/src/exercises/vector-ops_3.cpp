#include <iostream>

// The SYCL header
#include <SYCL/sycl.hpp>

namespace sycl = cl::sycl;

// <<Declare vector_addition kernel function object>>

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
    sycl::buffer<sycl::float4, 1> buf_a(&a, sycl::range<1>{1});
    sycl::buffer<sycl::float4, 1> buf_b(&b, sycl::range<1>{1});
    // define output buffer
    sycl::buffer<sycl::float4, 1> buf_c(&c, sycl::range<1>{1});

    // Submit a command group functor for execution on a queue. This functor
    // encapsulates the kernel and the data needed for its execution.
    myQueue.submit([&](sycl::handler &cgh) {
      // <<Request device memory access>>
      // read accessors
      auto a_acc = buff_a.get_access<sycl::access::mode::read>(cgh);
      auto b_acc = buff_b.get_access<sycl::access::mode::read>(cgh);
      // write accessor
      auto c_acc = buff_c.get_access<sycl::access::mode::write>(cgh);

      // Enqueue the kernel for execution using the `single_task` API
      cgh.single_task<class vector_addition>([=]() {
        // <<Complete the vector addition computation>>
        // calculate: c = a+b;
      });
    });
  }
  // End SYCL scope

  // validation checks
  {
    // Simple vector swizzles are available in SYCL for the cl::sycl::vec class
    // for up to width of 4 and are defined as functions, e.g. a.xy()
    // The cl::sycl::vec class works for host as well so the same functionality
    // is available on the host application.
    std::cout << "result (c=a+b): " << c.x() << " " << c.y() << " " << c.z()
              << " ";
    std::cout << c.w() << std::endl;
  }
  return 0;
}
