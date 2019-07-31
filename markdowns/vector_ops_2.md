# Device Memory using Buffers and Accessors

## Setup Device Memory - **Buffers**

### Description

In order to handle data on the device memory we need to create SYCL buffers.

The constructor for buffers for a raw data pointer to the data to be managed is the following:

```cpp
cl::sycl::buffer<typename T, int dimensions>(
    T* ptr, 
    cl::sycl::range<dimensions>(int range_size)
);
```

### Task

Create buffers for the 2 input vectors as well as for the output one.

Location in the source code:

```cpp
// <<Setup device memory>>
```

<details><summary>Hint</summary>
<p>

```cpp
// buffer for input 1
sycl::buffer<sycl::float4, 1> buf_a(&a, cl::sycl::range<1>{1});
```

</p>
</details>

## Access Device Memory - **Accessors**

### Description

SYCL has the concept of accessors which are used to access request control over the device memory from the buffer objects.

The different access modes are encapsulated in the following enum class:

```cpp
enum class mode { 
  read,
  write, 
  read_write, 
  discard_wirte, 
  discard_read_write,
  atomic
};
``` 
that lives in the `access` namespace.

At this stage we are only going to focus on the more common ones: `read`, `write`, and `read_write`.

A SYCL accessor can be created from a buffer by using the following construct:

```cpp
// e.g., read access to buffer memory
auto sycl_acc = sycl_buf.get_access<cl::sycl::access::mode::read>(cgh)
```

where `cgh` is an instance of the SYCL command group handler object `cl::sycl::handler`. Accessors are required to be created inside the command group for which they will be used.

### Task

Request access from the buffers for access to the data on the device.
- Read access from the input buffers
- Write access from the output buffer

Location in the source code:

```cpp
// <<Request device memory access>>
```

<details><summary>Hint</summary>
<p>

```cpp
// read accessor for the memory in `buf_a`
auto a_acc = buf_a.get_access<sycl::access::mode::read>(cgh);
```

</p>
</details>

# Run it!

@[Hello World from SYCL]({"stubs": ["src/exercises/vector-ops_2.cpp"],"command": "sh /project/target/run.sh vector-ops_2", "layout": "aside"})
