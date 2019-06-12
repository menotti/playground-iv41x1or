# Hello World

This first exercise will guide you through the steps involved in writing your first SYCL application. In true first application fashion the aim will be to simply print "Hello World" to the console.

## Including the SYCL Header File

Everything you need to write a SYCL application is included in the header file `CL/sycl.hpp`.

* Include the SYCL runtime header.

`#include <CL/sycl.hpp>`

## Creating a Queue

In SYCL there are different ways to configure and select the devices we want to use. SYCL provides default selections for the most common use cases, and a `cl::sycl::queue` is used to submit the work. A `cl::sycl::queue` can be default constructed and in this case it will ask the SYCL runtime to select a device for you based on what's available. There are other ways to ask SYCL to select a specific device based on more specific criteria and we will cover in a later exercise.

* Default construct a `cl::sycl::queue` object called `myQueue`.

`cl::sycl::queue myQueue(selector);`

## Creating a Command Group

In SYCL a task is represented by what's called a command group. A command group contains a kernel function which can be executed on a device and any data dependencies that kernel function has. A command group is defined using a C++ function object (either a lambda function or a struct or class with a function call operator). The C++ function object must take a single parameter; a `cl::sycl::handler &`, which is used to link together data the kernel function and it's data depencies.

In this exercise we have provided the command group for you.

`myQueue.submit([&](cl::sycl::handler &cgh)`

## Creating an Output Stream

In SYCL there are various objects which can be used to access data from within a kernel which are generally constructed within the scope of a command group. One of the simplest, which we are going to use in this exercise is a `cl::sycl::stream`. A `cl::sycl::stream` is a buffer output stream, behaving similarly to `std::ostream`, with the main difference being that it does not output to the console directly and instead buffers the output until after the kernel function is finished executing. A `cl::sycl::stream` must be constructed with three parameters, the maximum size of the buffer in bytes, the maximum length of a statement in bytes and the `cl::sycl::handler` associated with the command group scope it is created in.

* Construct a `cl::sycl::stream` with a maximum buffer size of `1024`, a maximum statement length of `128` and the `cl::sycl::handler` provided by the command group function object.

`cl::sycl::stream os(1024, 80, cgh);`

## Defining a Kernel Function

In SYCL there are various ways to define a kernel function that will execute on a device depending on the kind of parallelism you want and the different features you require. The simplest of these is the `cl::sycl::handler::single_task` function, which takes a single parameter, being a C++ function object and executes that function object exactly once on the device. The C++ function object does not take any parameters, however it is important to note that if the function object is a lambda it must capture by value and if it is a struct or class it must define all members as value members.

In this exercise we have provided the kernel function for you.

```
cgh.single_task<class hello_world>([=]() {    
       /* output "Hello World" to the console */
       os << "Hello, World!\n";
    });
```

## Outputing "Hello World"

From within the kernel function you can output to the `cl::sycl::stream` object using the `<<` operator as you would for `std::ostream` or `std::cout`.

* Stream the text `Hello World` to the console from within the kernel function.

`os << "Hello, World!\n";`

## Cleaning Up

One of the best features of SYCL is that it makes great use of C++ RAII (resource aquisition is initialisation), meaning that there is no explicit cleanup, everything is done via the SYCL object destructors. In this case the destructor of the `cl::sycl::stream` object will wait for the command group which is accessing it to complete and then ensure the buffer has been output to the console before returning.

# Run it!

@[Hello World from SYCL]({"stubs": ["src/exercises/hello_world.cpp"],"command": "sh /project/target/run.sh hello_world", "layout": "aside"})
