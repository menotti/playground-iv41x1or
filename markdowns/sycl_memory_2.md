# SYCL Memory and Synchronization: Read Hardware Information

`size_t wgroup_size = 32;`

We set the Work Group size that will be used. This is manually set as 32 which will work on all devices but it's important if you are optimizing for specific hardware to understand how to calculate the optimal work group size.

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

@[Parallel Reduction]({"stubs": ["src/exercises/memory_2.cpp"] "layout": "aside"})