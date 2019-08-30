# Host Setup and SYCL Queue

This exercise is a slightly modified version of the vector addition we did in the previous example. You are going to take over in this one and complete the code for this application by yourself. Instructions are provided on each step of completion, so you should be able to do it. Let's begin. 

> By now, you should know that you need to include the SYCL header file in order to use SYCL in your application. It is already included at the top of the source file - `#include <CL/sycl.hpp>`.

## Host Setup

### Description

The first step is to initialize the vector data on the host.

We will be using:

```cpp
cl::sycl::float4
```

which is a type alias for

```cpp
cl::sycl::vec<float, 4>
```

It is a SYCL type struct that provides OpenCL vector functionality for host and device.

### Task

Define 2 input vectors and 1 output vector.

Inputs:
 - vector `a`: `{1.0, 1.0, 1.0, 1.0}`
 - vector `b`: `{1.0, 1.0, 1.0, 1.0}`

Output:
- vector `c`: `{0.0, 0.0, 0.0, 0.0}`

Location in the source code:

```cpp
// <<Setup host memory>>
```

<details><summary>Hint</summary>
<p>

```cpp
sycl::float4 a = { 1.0f, 1.0f, 1.0f, 1.0f }; // input 1
```

</p>
</details>

## Initialize SYCL Queue

### Description

SYCL queue is constructed from the selection of a supported device.

The system is set to always force the execution of the SYCL examples on the CPU device. Thus, the default selector will select the CPU because of its heuristics to identify the supported platforms and device on our system.

### Task

Initialize a SYCL queue with either a CPU or default device selector.

Location in the source code:

```cpp
// <<Setup SYCL queue>>
```

<details><summary>Hint</summary>
<p>

```cpp
sycl::queue myQueue(sycl::default_selector{}); 
// explicitly target the CPU: sycl::cpu_selector{}
```

</p>
</details>

# Run it!

@[Hello World from SYCL]({"stubs": ["src/exercises/vector-ops_1.cpp"],"command": "sh /project/target/run.sh vector-ops_1", "layout": "aside"})
