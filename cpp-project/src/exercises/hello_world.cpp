#include <iostream>
/* include the SYCL runtime header */

int main (int argc, char *argv[]) {

  /* construct a queue object called myQueue */

  myQueue.submit([&](cl::sycl::handler &cgh) {

    /* construct a stream object */

    cgh.single_task<class hello_world>([=]() {
       
       /* output "Hello World" to the console */
        
    });
  });
}
