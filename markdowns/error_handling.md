# Error Handling

In general, there are two kinds of errors in SYCL. These are synchronous and asynchronous. 

Synchronous errors are classical C++ exceptions, thrown whenever the user calls a function with wrong arguments. These can be caught with a try..catch block.

Asynchronous errors, on the other hand, are those that describe faults in asynchronously executed code, for example inside a command group or a kernel. Since they can occur in a different stackframe, asynchronous error cannot be propagated up the stack. By default, they are considered 'lost'. The way in which we can retrieve them is by providing an error handler function.

## Creating an Exception Handler

The handler is a function object that accepts an exception_list [link] parameter. The parameter is an iterable list of std::exception_ptr objects. In our simple handler, we rethrow the pointer (there is no way to read from it directly), catch it, and output the exception description.

`auto exception_handler = [] (sycl::exception_list exceptions) {`

## Execute With Wrong Parameters

We setup a default queue and supply it with an invalid kernel. The reason why this code is erroneous is unimportant for now (it has to do with work-group sizes). Finally, we call queue::wait_and_throw [link]. This function blocks and waits for all enqueued tasks to finish. Then, it sends all asynchronous exceptions to our handler. Additionally, it is possible, but very unlikely, for it to directly throw a synchronous exception. For completeness, we also catch these.

```
queue.submit([&] (sycl::handler& cgh) {
   auto range = sycl::nd_range<1>(sycl::range<1>(1), sycl::range<1>(10));
   cgh.parallel_for<class invalid_kernel>(range, [=] (sycl::nd_item<1>) {});
});
```

You might be wondering why the exception handler has to take an exception list rather than a single exception as the argument. A single wait_and_throw request might report multiple exceptions, so it is convenient to group them into a list object. Each request has a single list corresponding to it, so the user is not burdened with manually checking which errors are in which group.

## Run It

This example intentionally throws an exception and we can see the output

@[Error Handling With SYCL]({"stubs": ["src/exercises/error_handling.cpp"],"command": "sh /project/target/run.sh error_handling", "layout": "aside"})
