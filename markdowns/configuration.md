# Getting Started with SYCL

## How does SYCL work?

A SYCL implementation consists of two main components; a SYCL device compiler, which compiles your code for OpenCL devices, and a SYCL runtime library which provides the high level interface writing SYCL applications and the runtime for executing your device code on OpenCL devices.

## What does SYCL run on?

SYCL can target a wide range of OpenCL devices on any given system such as multi-core CPUs, GPU, FPGA, DSPs and other kinds of accelerators and specialised processors.

The ComputeCpp package provides a tool called `computecpp_info`, which can be used for a variety of things, but primarily for  detecting supported devices on your system that can be used by ComputeCpp.

For the purposes of demonstration we can run `computecpp_info` here to display the OpenCL device(s) available to this tutorial.

@[ComputeCpp Info]({"command": "sh /project/target/validate.sh"})

**Note that this tutorial is running in a cloud instance and so is using what we call the "host" only. 

As you can see in the computecpp_info output the "host" is a CPU. Although it is unlikely to offer any performance improvements in the absence of a GPU it enables us to run our SYCL code using ComputeCpp.
