# SYCL Memory and Synchronization: Read Hardware Information

We will read the hardware information in order to find out some specifics about the device we want our application to run on.

```
  sycl::device device = sycl::default_selector{}.select_device();
  sycl::queue queue(device, [] (sycl::exception_list el) {
      for (auto ex : el) { std::rethrow_exception(ex); }
    } );
```

The first thing we do is initialize a queue in a slightly different manner than before. Instead of passing a selector to the queue constructor, we request it to return a selected device object. This allows us to access hardware information.

`device.get_info<sycl::info::device::max_work_group_size>`

The device::get_info function has a single template parameter specifying the piece of information that we want to retrieve. info::device::max_work_group_size is defined to be the maximum number of work-items in a work-group executing on a single compute unit. Exceeding this size should result in an error. It is not necessarily the optimal size, but it can be expected to yield good performance.

`auto part_size = wgroup_size * 2;`

We initialize a part_size variable to be the number of elements in the array that work-group reduces. Since each work-item initially reduces two elements, it is twice the work-group size.

```
if (!has_local_mem
      || local_mem_size < (wgroup_size * sizeof(int32_t)))
  {
       throw "Device doesn't have enough local memory!";
  }
```

We also test the device for the local memory size - we cannot perform the reduction if there is too little of it or if local memory is unsupported altogether. Of course, in a real-world application a special case would have to be made to also support such devices.

@[Parallel Reduction]({"stubs": ["src/exercises/memory_2.cpp"],"command": "sh /project/target/run.sh memory_2", "layout": "aside"})