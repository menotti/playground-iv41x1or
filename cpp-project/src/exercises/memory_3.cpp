  #include <array>
  #include <cstdint>
  #include <iostream>
  #include <random>
  #include <cassert>

  #include <CL/sycl.hpp>
  class reduction_kernel;
  namespace sycl = cl::sycl;

  int main(int, char**) {
    std::array<int32_t, 16> arr;

    std::mt19937 mt_engine(std::random_device{}());
    std::uniform_int_distribution<int32_t> idist(0, 10);

    std::cout << "Data: ";
    for (auto& el : arr) {
      el = idist(mt_engine);
      std::cout << el << " ";
    }
    std::cout << std::endl;

    sycl::buffer<int32_t, 1> buf(arr.data(), sycl::range<1>(arr.size()));

    sycl::device device = sycl::default_selector{}.select_device();
    
    sycl::queue queue(device, [] (sycl::exception_list el) {
       for (auto ex : el) { std::rethrow_exception(ex); }
    } );

    // <<Set up queue and check device information>>
	/* Here we manually set the Work Group size to 32, 
    but there may be a more optimal size for your device */
    auto wgroup_size = 32;
    
	auto part_size = wgroup_size * 2;

    auto has_local_mem = device.is_host()
        || (device.get_info<sycl::info::device::local_mem_type>()
        != sycl::info::local_mem_type::none);
    auto local_mem_size = device.get_info<sycl::info::device::local_mem_size>();
    if (!has_local_mem
      || local_mem_size < (wgroup_size * sizeof(int32_t)))
    {
       throw "Device doesn't have enough local memory!";
    }
  
    // <<Reduction loop>>
    auto len = arr.size();
    while (len != 1) {
       // division rounding up
       auto n_wgroups = (len + part_size - 1) / part_size;

       queue.submit([&] (sycl::handler& cgh) {
          sycl::accessor <int32_t, 1, sycl::access::mode::read_write, sycl::access::target::local>
                         local_mem(sycl::range<1>(wgroup_size), cgh);

          auto global_mem = buf.get_access<sycl::access::mode::read_write>(cgh);

          cgh.parallel_for<class reduction_kernel>(
               sycl::nd_range<1>(n_wgroups * wgroup_size, wgroup_size),
               [=] (sycl::nd_item<1> item) {
             // Perform load into local memory

             // Reduce into one element

             // Write group result to global memory
          });
       });
    queue.wait_and_throw();

    len = n_wgroups;
  }

    auto acc = buf.get_access<sycl::access::mode::read>();
    std::cout << "Sum: " << acc[0] << std::endl;

    return 0;
  }