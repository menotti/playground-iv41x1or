# SYCL Memory and Synchronization: Reduction loop

`auto n_wgroups = (len + part_size - 1) / part_size;`

Inside the reduction loop, we first find the number of work-groups for this step of reduction. It is the length len left to be reduced divided by the number of elements that each work-group reduces.

`sycl::accessor<int32_t, 1, sycl::access::mode::read_write, sycl::access::target::local> local_mem(sycl::range<1>(wgroup_size)`

Next, in the command group, we allocate a part of local memory by creating an accessor with access::target::local and a range equal to the work-group size. We checked the memory size earlier, so we know that it is available. As stated above, this region of memory looks different to each work-group and its use is for temporary storage.

You might wonder, why do we even bother with using local memory when we could carry out the whole operation in global? The answer is that it is much faster. Local memory is (usually) physically closer to the chip than global and it does not suffer from problems such as false sharing, since it is exclusive to each compute unit. It is therefore a good idea to always carry out all temporary operations in local memory for best performance.

`auto global_mem = buf.get_access<sycl::access::mode::read_write>(cgh);`

We also obtain an accessor to the data available in global memory. This time get_access is explicitly qualified with access::target::global_buffer, while previously it took on that value by default.

```
cgh.parallel_for<class reduction_kernel>(
      sycl::nd_range<1>(n_wgroups * wgroup_size, wgroup_size),
      [=] (sycl::nd_item<1> item)
```

Lastly, we launch a parallel kernel. We use the nd_range variant, which allows us to specify both the global and local size. The nd_range constructor takes in two range objects of the same dimensionality as itself. The first one describes the number of work-items per dimension (recall that there can be up to three dimensions). The second range argument to nd_range<n> describes the number of work-items in a work-group. To find the number of work-groups per dimension, divide the first argument by the second. In this case the result is n_wgroups, which is how many work-groups will be instantiated. In this variant the kernel lambda takes an nd_item argument. It represents the current work-item and features methods to get detailed information from it, such as local, global, and work-group info.

Since each step of the reduction loop produces one number per work-group, we set the len to n_wgroups on every iteration, which will continue reducing over the results.

@[Parallel Reduction]({"stubs": ["src/exercises/memory_3.cpp"],"command": "sh /project/target/run.sh memory_3", "layout": "aside"})