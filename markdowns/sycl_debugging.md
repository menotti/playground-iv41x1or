# Debugging SYCL

### Debugging on the Host

One important difference between SYCL and OpenCL is that while OpenCL kernels can only execute on OpenCL devices, a SYCL kernel can also execute on the SYCL host device. This mode does not require an OpenCL implementation for the CPU and can be used when none is available. Moreover, in this mode the code is executed as standard machine code and can be debugged as such. This means that problems in your SYCL kernels can be found really easily without having to resort to device-specific debuggers and awkward hardware manipulation. You can use your debugger of choice and break at any point inside a kernel. If the invocation is a parallel_for, the host code will spawn OS threads, so standard multi-threaded debugging methods can be applied.

### Debugging on the Device

This works well most of the time, but not all kinds of problems can be debugged like this. If an issue only happens when running on an OpenCL device, it has to be analyzed differently. There are several points at which something might go wrong. Most often it is a user error - something to do with different type widths, a data race which can only be observed in device mode, etc.

In cases like these, it might be necessary to debug the code running on OpenCL or even the specific hardware. A few tools exist to make this process slightly less painful:

 * Oclgrind simulates a full OpenCL environment that can detect a variety of errors which wont necessarily manifest in host mode.
 * GPUVerify is a formal analysis tool which can 'prove' that a bit of code is correct in certain respects. Unfortunately, it only accepts OpenCL C code, which means you would have to translate your SYCL kernel to that.
 * Hardware vendors often provide debugging tools specific to their devices.

### Print to Stream

The cl::sycl::stream constructor takes two numbers - the maximum buffer size and the maximum statement size. The buffer size controls how many bytes in total can be output through the stream in the kernel invocation. The statement size controls how many bytes can be output in a single statement, that is everything between between the first stream::operator<< and the semicolon. For example, in out << a << b << '\n';, the maximum statement size is a limit to sizeof(a) + sizeof(b) + sizeof('\n'). The last parameter is the command group that the stream will be used in.

In the kernel, we output a string and a newline manipulator - SYCL provides a few manipulators analogous to those in the C++ standard library.

@[Stream Print]({"stubs": ["src/exercises/sycl_debugging.cpp"],"command": "sh /project/target/run.sh sycl_debugging", "layout": "aside"})