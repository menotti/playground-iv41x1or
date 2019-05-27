#include <iostream>
#include <CL/sycl.hpp>

/* include the SYCL runtime header */
class hello_world;

int main (int argc, char *argv[]) {
    /* construct a queue object called myQueue */
    cl::sycl::default_selector selector;

    /* Queues are used to enqueue work.
    * In this case we construct the queue using the selector. Users can create
    * their own selectors to choose whatever kind of device they might need. */
    cl::sycl::queue myQueue(selector);

    myQueue.submit([&](cl::sycl::handler &cgh) {
        /* construct a stream object */
        cl::sycl::stream os(1024, 80, cgh);

        cgh.single_task<class hello_world>([=]() {
           /* output "Hello World" to the console */
           os << "Hello, World!\n";
        });
    });
}