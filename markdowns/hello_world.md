# Hello World

This first exercise will guide you through the steps involved in writing your first SYCL application. We'll work through the equivalent of "hello world" for parallel programming, a vector add. This will add two vectors together, but crucially SYCL will enable this addition to be done in parallel.

## Including the SYCL Header File

The first line in every SYCL application is to include the header file `CL/sycl.hpp`.

`#include <CL/sycl.hpp>`

## Setup Host Storage

In main, we begin by setting up host storage for the data that we want to operate on. Our goal is to compute c = a + b, where the variables are vectors. To help us achieve this, SYCL provides the vec<T, size> type, which is a vector of a basic scalar type. It has template parameters for the scalar type and the size. It is meant to be used more like a geometrical vector than std::vector, and so it only supports sizes of up to 16. But dont despair, there are plenty of ways to work on larger sets of data. We use float4, which is just vec<float, 4>.

```
sycl::float4 a = { 1.0, 2.0, 3.0, 4.0 };
sycl::float4 b = { 4.0, 3.0, 2.0, 1.0 };
sycl::float4 c = { 0.0, 0.0, 0.0, 0.0 };
```

## Selecting Your Device

In SYCL there are different ways to configure and select the devices we want to use. SYCL provides a default selector that tries to select the most appropriate device in your system. It's possible to use a custom selector but since we only have one device we use the default selector.

`cl::sycl::default_selector selector;`

## Setting up a SYCL Queue

In order to send our tasks to be scheduled and executed on the target device we need to use a SYCL queue. We set this up and pass it our selector so that it knows what device to select when running the tasks.

`cl::sycl::queue myQueue(selector);`

## Setup Device Storage

On most systems, the host and the device do not share physical memory. For example, the CPU might use RAM and the GPU might use its own on-die VRAM. SYCL needs to know which data it will be sharing between the host and the devices.

For this purpose, SYCL buffers exist. The buffer<T, dims> class is generic over the element type and the number of dimensions, which can be one, two or three. When passed a raw pointer like in this case, the buffer(T* ptr, range size) constructor takes ownership of the memory it has been passed. This means that we absolutely cannot use that memory ourselves while the buffer exists, which is why we begin a C++ scope. At the end of their scope, the buffers will be destroyed and the memory returned to the user. The size argument is a range<dims> object, which has to have the same number of dimensions as the buffer and is initialized with the number of elements in each dimension. Here, we have one dimension with one element.

Buffers are not associated with a particular queue or context, so they are capable of handling data transparently between multiple devices. They also do not require read/write information, as this is specified per operation.

```
sycl::buffer<sycl::float4, 1> a_sycl(&a, sycl::range<1>(1));
sycl::buffer<sycl::float4, 1> b_sycl(&b, sycl::range<1>(1));
sycl::buffer<sycl::float4, 1> c_sycl(&c, sycl::range<1>(1));
```

## Executing the Kernel

### Creating a Command Group

The whole thing is technically a single function call to `queue::submit`. `submit` accepts a function object parameter, which encapsulates a command group. For this purpose, the function object accepts a command group handler constructed by the SYCL runtime and handed to us as the argument. All operations using a given command group handler are part of the same command group.

`myQueue.submit([&](cl::sycl::handler &cgh)`

A command group is a way to encapsulate a device-side operation and all its data dependencies in a single object by grouping all the related commands (function calls). Effectively, what this achieves is preventing data race conditions, resource leaking and other problems by letting the SYCL runtime know the prerequisites for executing device-side code correctly.

### Data Accessors

In our command group, we first setup accessors. In general, these objects define the inputs and outputs of a device-side operation. The accessors also provide access to various forms of memory. In this case, they allow us to access the memory owned by the buffers created earlier. We passed ownership of our data to the buffer, so we can no longer use the float4 objects, and accessors are the only way to access data in buffer objects.

```
auto a_acc = a_sycl.get_access<sycl::access::mode::read>(cgh);
auto b_acc = b_sycl.get_access<sycl::access::mode::read>(cgh);
auto c_acc = c_sycl.get_access<sycl::access::mode::discard_write>(cgh);
```

The buffer::get_access(handler&) method takes an access mode argument. We use access::mode::read for the arguments and access::mode::discard_write for the result. discard_write can be used whenever we write to the whole buffer and do not care about its previous contents. Since it will be overwritten entirely, we can discard whatever was there before.

The second parameter is the type of memory we want to access the data from. We will see the available types of memory in the section on memory accesses. For now we use the default value.

### Defining a Kernel Function

In SYCL there are various ways to define a kernel function that will execute on a device depending on the kind of parallelism you want and the different features you require. The simplest of these is the `cl::sycl::handler::single_task` function, which takes a single parameter, being a C++ function object and executes that function object exactly once on the device. The C++ function object does not take any parameters, however it is important to note that if the function object is a lambda it must capture by value and if it is a struct or class it must define all members as value members.

```
   cgh.single_task<class vector_addition>([=] () {
      c_acc[0] = a_acc[0] + b_acc[0];
   });
});
```

## Cleaning Up

One of the features of SYCL is that it makes use of C++ RAII (resource aquisition is initialisation), meaning that there is no explicit cleanup and everything is done via the SYCL object destructors.
```
{
   ...
}
```

# Run it!

@[Hello World from SYCL]({"stubs": ["src/exercises/hello_world.cpp"],"command": "sh /project/target/run.sh hello_world", "layout": "aside"})
