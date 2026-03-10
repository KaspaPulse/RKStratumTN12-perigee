// Windows stub implementation for risc0-zkvm-platform's sys_alloc_aligned
//
// WORKAROUND: Temporary workaround for Windows linking errors with risc0-zkvm-platform
//
// ERROR ENCOUNTERED:
// ==================
// When building on Windows (tn12 branch) with MSVC toolchain, the linker fails with:
//
//   error LNK2019: unresolved external symbol sys_alloc_aligned referenced in function
//   _ZN19risc0_zkvm_platform7syscall15sys_alloc_words17hd3ca7735ddf0b22bE
//
// This affects multiple crates that transitively depend on kaspa-txscript:
//   - kaspa-wallet-pskt
//   - kaspa-wrpc-client
//   - kaspa-grpc-simple-client-example
//   - rothschild
//
// WHY THIS SOLUTION:
// ==================
// We provide a Windows-specific implementation of sys_alloc_aligned()
// and sys_free_aligned() using MSVC's native _aligned_malloc()/_aligned_free()
// functions. This satisfies the linker's requirement for these symbols.
//
// IMPORTANT NOTES:
// ================
// - These functions are called by risc0-zkvm-platform but are only used during ZK proof
//   execution, not during verification-only use cases (which is how Kaspa uses it).
// - The implementation uses Windows-specific functions (_aligned_malloc, _aligned_free)
//   which are part of the MSVC runtime library, so no additional dependencies are required.
// - This is a temporary workaround until risc0-zkvm-platform adds proper Windows support.
//
// TODO: Remove this workaround when risc0-zkvm-platform adds proper Windows support.
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

