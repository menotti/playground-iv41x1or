# SYCL Kernel Programming - The single_task API

## Declare the `vector addition` kernel

### Description

By specification, an unnamed type is an invalid template argument for classes used to name SYCL kernels. Therefore, you need to at least declare the kernel class before using it.

The following examples are valid SYCL kernel names:

```cpp
// class
class MyKernelClass;
// struct
struct MyKernelStruct;
// enum class
enum class MyKernelEnum : int;
```

### Task

Forward declare the `vector_addition` class functor before the `int main` entry point of the application.

Location in the source code:

```cpp
// <<Declare vector_addition kernel function object>>
```

<details><summary>Hint</summary>
<p>

```cpp
class vector_addition;
```

</p>
</details>

## Implement the `vector addition` kernel

### Description

Now we need to enqueue and the vector addition kernel for execution.

A kernel that is executed on one thread using `NDRange(1,1,1)` can be enqueued using the `cl::sycl::single_task` API:

```cpp
single_task<typename kernel_lambda_name>([=](){});
```

This is equivalent to executing a kernel on a single compute unit with a single work-group of only one work-item. Thus, we can access the values of the accessor objects directly by using the `0th` index as follows:

```cpp
// e.g, assign accessor element in the kernel body
acc[0] = someValue;
```

### Task

Complete the vector addition kernel code where the accessors of `a`, `b`, `c` make the vectors available for calculating `c = a + b`.

Location in the source code:

```cpp
// <<Complete the vector addition computation>>
```

<details><summary>Hint</summary>
<p>

```cpp
c_acc[0] = a_acc[0] + b_acc[0];
```

</p>
</details>

# Run it!

@[Hello World from SYCL]({"stubs": ["src/exercises/vector-ops_3.cpp"],"command": "sh /project/target/run.sh vector-ops_3", "layout": "aside"})
