# Introduction to SYCL

## What is SYCL?

SYCL is a royalty-free open standard produced by the Khronos Group, the standards body responsible for other well known standards such as OpenGL, Vulkan or OpenCL. SYCL defines a high-level single source C++ programming for programming heterogeneous architectures such as GPUs, FPGAs, DSPs and other kinds of accelerators.

SYCL is based on top of OpenCL, another standard from the Khronos Group which defines a low-level C api and C based kernel language for writing heterogeneous applications. SYCL provides the same performance portability and access to OpenCL hardware as with traditional OpenCL however also provides a high-level interface which removes much of the boiler plate code typical to OpenCL, but also provides many additional features such as data dependency analysis and task scheduling.

SYCL is single source, which means that rather than having your host side code and the kernel code (code which is compiled for an OpenCL device) defined separately as is the case with OpenCL, you have both your host code and kernel code in the same C++ source file. This opens up users to a range of benefts such as stronger type safety and templated kernel code.

SYCL is entirely standard C++11, which means there are not language extensions or attributes required.

## This Tutorial

This tutorial aims to teach you everything you need to know to write SYCL applications for a GPU, it will cover how to discover a device to execute work on, different ways to express parallelism, how to manage your data and much more.

This tutorial will use SYCL 1.2.1 which is the latest version of the standard as of Dec 2017.
