#include <CL/sycl.hpp>
namespace sycl = cl::sycl;
class printkernel;

int main(int, char **) {
  sycl::queue queue(sycl::default_selector{});

  queue.submit([&](sycl::handler &cgh) {
    sycl::stream out(1024, 256, cgh);

    cgh.single_task<class printkernel>(
        [=] { out << "Hello stream!" << sycl::endl; });
  });

  /* Wait for the command queue to finish!
   * This explicit synchronisation point is required because a SYCL
   * command queue submits the command group inside it asynchronously. Thus,
   * if there are no dependencies such as memory objects (buffers) or other
   * kernels, the program control will be returned back to the host device
   * before starting the execution of the kernel. */
  queue.wait_and_throw();

  return 0;
}
