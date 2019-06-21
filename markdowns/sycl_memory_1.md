# SYCL Memory and Synchronization

While for simple computations it is okay to operate purely on work-items, any more complex workload will require finer-grained control. Unfortunately, this comes at the cost of introducing some complexity. Hopefully though, we can clear everything up!

You might remember that work-items are grouped into work-groups. The splitting into work-groups is not purely conceptual - it has very real implications on memory accesses and performance. Work-groups are independent of each other. In fact, there is no way to synchronize between them in a single kernel. For this reason, two work-groups should never write to the same memory location (although they can read shared data).

OpenCL and SYCL define a clear distinction between various regions in memory and rules that govern accesses to these. Everything on the CPU side is known as host memory. It is not directly accessible from kernels, but as we've seen, buffers and accessors provide facilities for copying host data to the device and accessing it there. The corresponding accessor target is access::target::host_buffer.

On the device side, more memory regions exist:

 * Global memory is available in the same form to all work-groups and items. It can be thought of as a device-side equivalent of RAM. The corresponding target, access::target::global_buffer, is the default target for buffer::get_access. In previous examples we didn't explicitly specify a target, so this one was used.

 * Local memory is specific to a single work-group. Work-groups cannot access others' local memory, but it is shared between all work-items in a group. It can be thought of as a user-controlled cache. It is especially useful for divide-and-conquer problems where each part of computation is handled by one work-group. Local memory can be used to store the result of such a computation. Local memory is allocated per kernel execution and it cannot be filled with host data, so you have to initialize it yourself. The canonical way to allocate it is to create a access::target::local accessor inside a command group, passing it the requested allocation size.

 * Private memory is a small region dedicated to each work-item. It is much like CPU register memory. All variables created in a kernel are stored in private memory. Additionally, dedicated private_memory objects can be created for this purpose.

 * Finally, constant memory is a read-only part of global memory, which similarly can reference a host-side buffer.

In this example we will try to compute an array reduction - the sum of all its elements. The overall structure of the example is shown in the console, you can see the code that initializes an array of random values to be added and prints these values.

```
std::cout << "Data: ";
  for (auto& el : arr) {
    el = idist(mt_engine);
    std::cout << el << " ";
  }
```

## Parallel reduction

## Overall Structure

@[Parallel Reduction]({"stubs": ["src/exercises/memory_1.cpp"],"command": "sh /project/target/run.sh memory_1", "layout": "aside"})


