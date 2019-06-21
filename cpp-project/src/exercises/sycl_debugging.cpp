#include <CL/sycl.hpp>
 namespace sycl = cl::sycl;

 int main(int, char**) {
   sycl::queue queue(sycl::default_selector{});

   queue.submit([&] (sycl::handler& cgh) {
       sycl::stream out(1024, 256, cgh);

       cgh.single_task<class printkernel>([=] {
       out << "Hello stream!" << sycl::endl;
     } );
     } );

   return 0;
 }