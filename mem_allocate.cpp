#include <stdlib.h>
#include <stddef.h>
#include <memory>
#include <vector>
#include <chrono>
#include <iostream>

/**
 * Allocator template to align buffer to Page boundary for better data transfer
 */
template <typename T>
struct aligned_allocator {
    using value_type = T;
    T* allocate(std::size_t num) {
        void* ptr = nullptr;
        if (posix_memalign(&ptr, 4096, num*sizeof(T))) {
            throw std::bad_alloc();
        }
        return reinterpret_cast<T*>(ptr);
  }
  void deallocate(T* p, std::size_t num) {
      free(p);
  }
};

int main ( int argc, char * argv [] ) {

    size_t size  = std::stoll(argv[1]);
    size_t size2 = std::stoll(argv[2]);

    // has to use O2 to "fast" allocate
    auto aligned_alloc_time_begin = std::chrono::high_resolution_clock::now();
    auto mem =  std::vector<unsigned char, aligned_allocator<unsigned char>>(1ULL<<size);
    auto aligned_alloc_time_end = std::chrono::high_resolution_clock::now();

    auto mem_alloc_time_begin = std::chrono::high_resolution_clock::now();
    auto mem2 =  std::vector<unsigned char>(1ULL<<size2);
    auto mem_alloc_time_end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> aligned_duration = aligned_alloc_time_end - aligned_alloc_time_begin;
    std::chrono::duration<double> non_aligned_duration = mem_alloc_time_end - mem_alloc_time_begin;

    std::cout << "TIME aligned mem allocation : " << aligned_duration.count() << "s" << std::endl;
    std::cout << "TIME non aligned mem allocation : " << non_aligned_duration.count() << "s" << std::endl;
    
    return 0;
}

