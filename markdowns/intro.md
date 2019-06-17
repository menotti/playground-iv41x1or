# Introduction to SYCL

## What is SYCL?

SYCL (pronounced ‘sickle’) is a royalty-free, cross-platform abstraction layer that builds on the underlying concepts, portability and efficiency of OpenCL that enables code for heterogeneous processors to be written in a “single-source” style using completely standard C. SYCL enables single source development where C template functions can contain both host and device code to construct complex algorithms that use OpenCL acceleration, and then re-use them throughout their source code on different types of data.

SYCL is entirely standard C++ so there are not language extensions or attributes required.

## This Tutorial

This tutorial aims to teach you the fundamentals of SYCL through the explanation of a simple application.

This tutorial will use ComputeCpp, a SYCL v1.2.1 conformant implementation.
