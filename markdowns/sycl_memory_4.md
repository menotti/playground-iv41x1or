# Using Local Memory

We'll now load the data into local memory, as we explained before using local memory can provide significant performance improvements.

```
  size_t local_id = item.get_local_linear_id();
  size_t global_id = item.get_global_linear_id();

  local_mem[local_id] = 0;

  if ((2 * global_id) < len) {
    local_mem[local_id] = global_mem[2 * global_id] + global_mem[2 * global_id + 1];
  }

  item.barrier(sycl::access::fence_space::local_space);
```

In the kernel, we firstly zero-initialize the local memory, since it can in fact contain garbage data. The key point here is that 0 is the invariant of our reduction, meaning that x + 0 = x, so we can add the whole array safely even if it isn't entirely filled with data to be reduced.

We divide our data into parts, each one being computed by a single work-group. The input data is required to be of even size, but it doesn't have to be a multiple of the work-group size. Hence, a few work-items in the last work-group can have no corresponding data. For this reason, the initial load from global to local memory is guarded by an if-statement. As mentioned in the "parallelism" section, this is usually a bad idea. In this case, however, it is okay, because at most one work-group will have divergent work-items. We use a small array for illustration purposes and a specialized kernel would technically be faster, but any real use case can be expected to have much more input data.

After the load is performed with an addition of the two elements corresponding to each work-item, we emit a barrier with a local memory fence. We have to stop for a bit and understand why this is necessary. In the OpenCL memory model, all operations across work-items have relaxed semantics. For example, in the following pseudocode we execute two functions in parallel over the same data:

### Relaxed Write Pseudo Code

```
  int x = 0;
  int y = 0;

  void thread_a() {
    write(x, 1);
    write(y, 2);
  }

  void thread_b() {
    int ly = load(y);
    int lx = load(x);
    printf("%i %i", lx, ly);
  }

  in_parallel(thread_a, thread_b);
```

In a relaxed memory model, work-item B can in fact print 0 2. This looks wrong, because work-item A must have written x into memory before it wrote y. The key point is that operation work-item B can observe A's operations in a different order. This 'really' helps hardware performance, but it comes at the cost of confusing behaviour. To deal with this problem, we have to emit memory fences. Moreover, even if we don't mind reordering, we might want to make sure that all results of write operations propagate between work-items - otherwise they could stay in per-work-item cache and not be visible across work-items.

To synchronize the state of memory, we use the item::barrier(access::fence_space) operation. A SYCL barrier does two things. Firstly, it makes sure that each work-item within the work-group reaches the barrier call. In other words, it guarantees that the work-group is synchronized at a certain point in the code. It is very important to make sure that 'either all work-items reach the barrier or none do'. For example, the following code is invalid:

### Branch Barrier

```
  if (local_id < 5) {
    item.barrier(sycl::access::fence_space::local_space);
  } else {
    item.barrier(sycl::access::fence_space::local_space);
  }
```

It looks innocent, but the problem is that the two instructions are not the same barrier. Work-items below local id 5 will get to the first barrier while the rest will get to the other one, and the execution will stall, both groups waiting on each other forever. A simple transformation of factoring the barrier call out of the conditional would fix it.

Secondly, item::barrier emits a memory fence in the specified space. It can be either access::fence_space::local_space, ::global_space or ::global_and_local. A fence ensures that the state of the specified space is consistent across all work-items within the work-group. Importantly, it is 'not possible' to synchronize between work-groups. They are entirely independent, and any write or read in the same global memory area done by two work-groups is a data race. For this reason, it is important to make sure each work-group only works on a dedicated region of global memory without crossover.

Next, we reduce each work-group's array in local memory:

### Reduce Into One Element

```
  for (size_t stride = 1; stride < wgroup_size; stride *= 2) {
    auto idx = 2 * stride * local_id;
    if (idx < wgroup_size) {
      local_mem[idx] = local_mem[idx] + local_mem[idx + stride];
    }

    item.barrier(sycl::access::fence_space::local_space);
  }
```

Since each iteration of the for loop depends on the previous one, we emit a barrier every time to synchronize work-items.

Lastly, write a single number which is the result of this work-group's reduction into global memory.

### Write Group Result To Global Memory

  if (local_id == 0) {
    global_mem[item.get_group_linear_id()] = local_mem[0];
  }

And the result is obtained if you press the "Run" button below:

@[Parallel Reduction]({"stubs": ["src/exercises/memory_4.cpp"],"command": "sh /project/target/run.sh memory_4", "layout": "aside"})