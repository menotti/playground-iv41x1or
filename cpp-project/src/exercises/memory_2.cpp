#include <array>
#include <cstdint>
#include <iostream>
#include <random>
#include <cassert>

#include <CL/sycl.hpp>
namespace sycl = cl::sycl;

int main(int, char**) {
  sycl::device device = sycl::default_selector{}.select_device();
  sycl::queue queue(device, [] (sycl::exception_list el) {
    for (auto ex : el) { std::rethrow_exception(ex); }
  });

  auto wgroup_size = device.get_info<sycl::info::device::max_work_group_size>();
  if (wgroup_size % 2 != 0) {
    throw "Work-group size has to be even!";
  }
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
  
  return 0;
}

