# Getting Started with SYCL

## Implementations

There are currently to work in progress implementations of the SYCL 1.2.1 standard:

Codeplay Software's [ComputeCpp Community Edition](https://codeplay.com/products/computesuite/computecpp).

Xilinx's open source [TriSYCL](https://github.com/triSYCL/triSYCL).

These tutorials will be using ComputeCpp.

## How does SYCL work?

A SYCL implementation consists of two main components; a SYCL device compiler, which compiles your code for OpenCL devices, and a SYCL runtime library which provides the high level interface writing SYCL applications and the runtime for executing your device code on OpenCL devices.

## What does SYCL run on?

SYCL can target a wide range of OpenCL devices on any given system such as multi-core CPUs, GPU, FPGA, DSPs and other kinds of accelerators and specialised processors.

The ComputeCpp installation provides a tool called `computecpp_info`, which can be used for a variety of things, primarily for verifying an instalation and detecting supported OpenCL devices on your system.

For the purposes of demonstration we can run `computecpp_info` here to display the OpenCL device(s) available to this tutorial.

@[ComputeCpp Info]({"command": "sh /project/target/validate.sh"})

**Note that this tutorial is still work in progress and currently only targets the host device, which means it is not yet running on a GPU, however it will behave in the same manner as if it were.**
