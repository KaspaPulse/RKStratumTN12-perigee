// Windows stub implementation for risc0-zkvm-platform's sys_alloc_aligned
// This function is called by risc0-zkvm-platform but not needed for verification-only use
//
// NOTE: IDE linter errors about missing headers are FALSE POSITIVES.
// This file only compiles on Windows with MSVC, where <malloc.h> exists.
// The code compiles successfully - verify with: cargo build --release

#ifdef _WIN32
#include <stddef.h>

// Explicitly declare Windows-specific functions (provided by MSVC runtime)
// These declarations satisfy the compiler even if the linter can't find the headers
void* _aligned_malloc(size_t size, size_t alignment);
void _aligned_free(void* ptr);

__declspec(dllexport) void* sys_alloc_aligned(size_t size, size_t alignment) {
    // Use _aligned_malloc on Windows (provided by MSVC runtime)
    return _aligned_malloc(size, alignment);
}

__declspec(dllexport) void sys_free_aligned(void* ptr) {
    // Use _aligned_free on Windows (provided by MSVC runtime)
    if (ptr) {
        _aligned_free(ptr);
    }
}
#endif  // _WIN32

