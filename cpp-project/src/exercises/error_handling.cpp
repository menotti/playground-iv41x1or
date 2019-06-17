#include <iostream>
#include <CL/sycl.hpp>

int main(int, char**) {
   auto exception_handler = [] (cl::sycl::exception_list exceptions) {
      for (std::exception_ptr const& e : exceptions) {
         try {
            std::rethrow_exception(e);
         } catch(cl::sycl::exception const& e) {
         std::cout << "Caught asynchronous SYCL exception:\n"
                   << e.what() << std::endl;
         }
      }
   };

   cl::sycl::queue queue(sycl::default_selector{}, exception_handler);

   queue.submit([&] (cl::sycl::handler& cgh) {
      auto range = cl::sycl::nd_range<1>(cl::sycl::range<1>(1), cl::sycl::range<1>(10));
      cgh.parallel_for<class invalid_kernel>(range, [=] (cl::sycl::nd_item<1>) {});
   });

   try {
      queue.wait_and_throw();
   } catch (cl::sycl::exception const& e) {
      std::cout << "Caught synchronous SYCL exception:\n"
      << e.what() << std::endl;
   }
   return 0;
}